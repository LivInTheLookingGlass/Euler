from atexit import register
from functools import partial
from itertools import chain
from os import environ, listdir, sep
from pathlib import Path
from platform import machine, processor, system, uname
from shutil import rmtree, which
from subprocess import check_call, check_output, run
from sys import path
from tempfile import TemporaryFile
from time import sleep
from typing import List, Set, Union
from uuid import uuid4
from warnings import warn

from pytest import fail, fixture, mark, skip, xfail

C_FOLDER = Path(__file__).parent
BUILD_FOLDER = C_FOLDER.joinpath('build')
path.append(str(C_FOLDER.parent.joinpath("python")))
from src.lib.utils import get_answer  # noqa: E402  # isort:skip

answers = {
    x: get_answer(x) for x in (
        *range(1, 18),
        *range(19, 21),
        22,
        25,
        30,
        34,
        76,
        836,
    )
}

# this is the set of problems where I have the right answer but wrong solution
known_slow: Set[int] = {}

# this is the set of problems where it has to access the filesystem, which pcc does not like
requires_io: Set[int] = {22}

# this is the set of problems where builds are not reproducible on PCC compiler
# PCC_no_reproducible: Set[str] = set()

# platform variables section
IN_WINDOWS = system() == 'Windows'
IN_OSX = system() == 'Darwin'
IN_TERMUX = bool(which('termux-setup-storage'))
IN_LINUX = (not IN_TERMUX) and (system() == 'Linux')
STANDARDS = ('c99', 'c11', 'c17')

if IN_TERMUX:
    # Termux can't make executable files outside of $HOME
    BUILD_FOLDER = Path.home().joinpath('build')  # pragma: no cover

_raw_NO_SLOW = environ.get('NO_SLOW')
try:
    _parsed_NO_SLOW: Union[str, int, None] = int(_raw_NO_SLOW)  # type: ignore
except Exception:
    _parsed_NO_SLOW = _raw_NO_SLOW
_raw_ONLY_SLOW = environ.get('ONLY_SLOW')
try:
    _parsed_ONLY_SLOW: Union[str, int, None] = int(_raw_ONLY_SLOW)  # type: ignore
except Exception:
    _parsed_ONLY_SLOW = _raw_ONLY_SLOW
_raw_NO_OPTIONAL_TESTS = environ.get('NO_OPTIONAL_TESTS')
try:
    _parsed_NO_OPTIONAL_TESTS: Union[str, int, None] = int(_raw_NO_OPTIONAL_TESTS)  # type: ignore
except Exception:
    _parsed_NO_OPTIONAL_TESTS = _raw_NO_OPTIONAL_TESTS

if _parsed_NO_SLOW and _parsed_ONLY_SLOW:
    warn("Test suite told to ignore slow tests AND run only slow tests. Ignoring conflicing options")  # pragma: no cover

# if in Termux, default to NO_SLOW, but allow users to explicitly override that decision
NO_SLOW = ((IN_TERMUX and _parsed_NO_SLOW is None) or _parsed_NO_SLOW) and not _parsed_ONLY_SLOW
ONLY_SLOW = _parsed_ONLY_SLOW and not _parsed_NO_SLOW
NO_OPTIONAL_TESTS = (_parsed_NO_OPTIONAL_TESTS is None and ONLY_SLOW) or _parsed_NO_OPTIONAL_TESTS

# this part isn't necessary, but I like having the binaries include their compile architecture
if IN_LINUX and processor() and ' ' not in processor():
    EXE_EXT = processor()
elif IN_WINDOWS:
    # processor() returns something too verbose in Windows
    EXE_EXT = "x86"
    if machine().endswith('64'):
        EXE_EXT += "_64"
elif IN_OSX:
    # processor() on OSX returns something too vague to be useful
    EXE_EXT = uname().machine.replace('i3', 'x')
elif IN_TERMUX:
    # processor() doesn't seem to work on Termux
    EXE_EXT = check_output('lscpu').split()[1].decode()
else:
    warn("Could not detect system architecture, defaulting to .exe")
    EXE_EXT = "exe"

GCC_BINARY = environ.get('GCC_OVERRIDE', 'gcc')
AOCC_BINARY = environ.get('AOCC_OVERRIDE', 'clang')

# compiler variables section
compilers: List[str] = []

if 'COMPILER_OVERRIDE' in environ:
    for comp in environ['COMPILER_OVERRIDE'].upper().split(','):
        if comp.strip().lower() == 'pcc':
            compilers.append(comp)
        elif comp.strip().lower() == 'tcc':
            compilers.extend(f'{comp}+{std}' for std in ('c99', 'c11'))
        else:
            compilers.extend(f'{comp}+{std}' for std in STANDARDS)
else:
    if not (IN_TERMUX and GCC_BINARY == 'gcc') and which(GCC_BINARY):  # Termux maps gcc->clang
        compilers.extend(f'GCC+{std}' for std in STANDARDS)
    if which('clang'):
        compilers.extend(f'CLANG+{std}' for std in STANDARDS)
    # if which('cl'):
    #     compilers.extend(f'CL+{std}' for std in STANDARDS)
    if which('pcc'):
        compilers.append('PCC')
    if which('tcc'):
        compilers.extend(f'TCC+{std}' for std in ('c99', 'c11'))
if not compilers:
    raise RuntimeError("No compilers detected!")  # pragma: no cover

COMPILER_LEN = len(max(compilers, key=len))  # make sure compiler fixtures are evenly spaced
BUILD_FOLDER.mkdir(parents=True, exist_ok=True)
CL_NO_64 = False
if 'CL' in compilers:
    OBJ_FOLDER = BUILD_FOLDER.joinpath('objs')
    OBJ_FOLDER.mkdir(exist_ok=True)
    _test_file = str(C_FOLDER.joinpath('src', 'assertions', 'x64_assert.c'))
    _test_exe = str(BUILD_FOLDER.joinpath('test_cl_64_support.out'))
    CL_NO_64 = not (run(['cl', '-Fe:{}'.format(_test_exe), '-Fo{}\\'.format(OBJ_FOLDER), str(_test_file)]).returncode)

_test_file = str(C_FOLDER.joinpath('src', 'p0000_template.c'))
GCC_NO_64 = False
if EXE_EXT == 'x86_64' and 'GCC' in compilers:
    # MingW GCC sometimes doesn't have 64-bit support on 64-bit targets
    # not knowing this will make the compiler macro test fail
    _test_exe = str(BUILD_FOLDER.joinpath('test_gcc_64_support.out'))
    GCC_NO_64 = bool(run([GCC_BINARY, _test_file, '-O0', '-m64', '-o', str(_test_exe)]).returncode)

CLANG_LINK_MATH = CLANG_ARCH = ''
if not IN_WINDOWS:
    CLANG_LINK_MATH = '-lm '
if 'CLANG' in compilers:
    _test_exe = str(BUILD_FOLDER.joinpath('test_clang_arch_native.out'))
    CLANG_ARCH = '-march=native' * (not run(['clang', _test_file, '-O0', '-march=native', '-o', _test_exe]).returncode)

SOURCE_TEMPLATE = "{}{}src{}p{{:0>4}}.c".format(C_FOLDER, sep, sep)
EXE_TEMPLATE = "{}{}p{{:0>4}}.{{}}.{}".format(BUILD_FOLDER, sep, EXE_EXT)
# include sep in the recipe so that Windows won't complain

GCC_TEMPLATE = "{} {{}} -O2 -lm -Wall -Wno-deprecated-declarations -Werror -std={} -march=native -flto -fwhole-program -o {{}}"
CLANG_TEMPLATE = "{} {{}} -O2 {} {} -Wall -Wno-deprecated-declarations -Werror -std={} {} -o {{}}"
if environ.get('COV') == 'true':
    GCC_TEMPLATE = GCC_TEMPLATE.replace('-O2', '-O1') + ' --coverage'
    CLANG_TEMPLATE = CLANG_TEMPLATE.replace('-O2', '-O1') + ' --coverage'

templates = {
    'PCC': "pcc -O2 -o {1} {0}",
}
for std in STANDARDS:
    templates.update({
        f'GCC+{std}': GCC_TEMPLATE.format(GCC_BINARY, std.replace('c', 'gnu')),
        f'CLANG+{std}': CLANG_TEMPLATE.format('clang', CLANG_LINK_MATH, CLANG_ARCH, std.replace('c', 'gnu'), '-DAMD_COMPILER=0'),
    })
    if std in ('c11', 'c17'):
        templates[f'CL+{std}'] = "cl -Fe:{{1}} -Fo{}\\ /std:{} -O2 -GL -GF -GW -Brepro -TC {{0}}".format(BUILD_FOLDER.joinpath('objs'), std)
    if std in ('c99', 'c11'):
        templates[f'TCC+{std}'] = "tcc -lm -std={} -Wall -Werror -o {{1}} {{0}}".format(std)


@register
def cleanup():  # pragma: no cover
    if 'PYTEST_XDIST_WORKER' not in environ and environ.get('NO_CLEANUP', 'false') != 'true':
        rmtree(BUILD_FOLDER)


@fixture(params=sorted(x.ljust(COMPILER_LEN) for x in compilers))
def compiler(request):  # type: ignore
    return request.param.strip()


# to make sure the benchmarks sort correctly
@fixture(params=("{:03}".format(x) for x in sorted(answers)))
def key(request):  # type: ignore
    return int(request.param)  # reduce casting burden on test


# to make sure the benchmarks sort correctly
@fixture(params=sorted(chain(listdir(C_FOLDER.joinpath("src", "tests")), ("{:03}".format(x) for x in answers))))
def c_file(request):  # type: ignore
    try:
        return SOURCE_TEMPLATE.format(int(request.param))
    except Exception:
        return C_FOLDER.joinpath("src", "tests", request.param)


@mark.skipif('NO_OPTIONAL_TESTS')
def test_compiler_macros(compiler):
    exename = EXE_TEMPLATE.format("test_compiler_macros", compiler)
    test_path = C_FOLDER.joinpath("src", "tests", "test_compiler_macros.c")
    check_call(templates[compiler].format(test_path, exename).split())
    flags = [bool(int(x)) for x in check_output([exename]).split()]
    expect_32 = (compiler == 'GCC' and GCC_NO_64) or (compiler == 'CL' and CL_NO_64)
    assert flags[0] == compiler.startswith("CL+")
    assert flags[1] == compiler.startswith("CLANG")
    assert flags[2] == compiler.startswith("GCC")
    assert flags[3] == compiler.startswith("PCC")
    assert flags[4] == compiler.startswith("TCC")
    assert flags[5] == compiler.startswith("EMCC")
    assert flags[6] == (EXE_EXT == "x86" or expect_32)
    assert flags[7] == (EXE_EXT == "x86_64" and not expect_32)
    assert flags[8] == ("arm" in EXE_EXT.lower() or "aarch" in EXE_EXT.lower())
    assert flags[9] == ("wasm" in EXE_EXT.lower())


@mark.skipif('NO_OPTIONAL_TESTS or ONLY_SLOW')
def test_is_prime(benchmark, compiler):
    from src.lib.primes import is_prime, prime_factors, primes
    MAX_PRIME = 1_000_000
    exename = EXE_TEMPLATE.format("test_is_prime", compiler)
    test_path = C_FOLDER.joinpath("src", "tests", "test_is_prime.c")
    args = templates[compiler].format(test_path, exename) + " -DMAX_PRIME={}".format(MAX_PRIME)
    check_call(args.split())
    with TemporaryFile('wb+') as f:
        run_test = partial(check_call, [exename], stdout=f)
        benchmark.pedantic(run_test, iterations=1, rounds=1)
        prime_cache = tuple(primes(MAX_PRIME))
        for line in f.readlines():
            num, prime, composite, idx = (int(x) for x in line.split())
            assert bool(prime) == bool(is_prime(num))
            assert bool(composite) == (not is_prime(num))
            assert composite == 0 or composite == next(iter(prime_factors(num)))
            assert idx == -1 or prime_cache[idx] == num

    # sometimes benchmark disables itself, so check for .stats
    if 'PYTEST_XDIST_WORKER' not in environ and hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 200 * MAX_PRIME // 1000000:
        fail("Exceeding 200ns average! (time={}s)".format(benchmark.stats.stats.max))


def test_problem(benchmark, key, compiler):
    if (NO_SLOW and key in known_slow) or (ONLY_SLOW and key not in known_slow) or (compiler == 'PCC' and key in requires_io):
        skip()
    filename = SOURCE_TEMPLATE.format(key)
    exename = EXE_TEMPLATE.format(key, compiler)  # need to have both to keep name unique
    check_call(templates[compiler].format(filename, exename).split())
    run_test = partial(check_output, [exename])

    if key in known_slow:
        answer = benchmark.pedantic(run_test, iterations=1, rounds=1)
    else:
        answer = benchmark(run_test)
    if isinstance(answers[key], int):
        assert answers[key] == int(answer.strip())
    else:
        assert answers[key] == answer.strip().decode()
    # sometimes benchmark disables itself, so check for .stats
    if 'PYTEST_XDIST_WORKER' not in environ and hasattr(benchmark, 'stats') and benchmark.stats.stats.median > 60:
        fail_func = xfail if key in known_slow else fail
        stats = benchmark.stats.stats
        fail_func("Exceeding 60s! (Max={:.6}s, Median={:.6}s)".format(stats.max, stats.median))

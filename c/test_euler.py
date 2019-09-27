from atexit import register
from functools import partial
from os import environ, makedirs, remove, sep
from os.path import expanduser
from pathlib import Path
from platform import machine, processor, system
from shutil import rmtree, which
from subprocess import CalledProcessError, check_call, check_output
from sys import path
from tempfile import TemporaryFile
from typing import List, Set, Union
from warnings import warn

from pytest import fail, fixture, skip, xfail

C_FOLDER = Path(__file__).parent
path.append(str(C_FOLDER.parent.joinpath("python")))

answers = {
    1: 233168,
    2: 4613732,
    3: 6857,
    5: 232792560,
    6: 25164150,
    7: 104743,
    8: 23514624000,
    9: 31875000,
    10: 142913828922,
    14: 837799,
    34: 40730,
    76: 190569291,
}

known_slow: Set[int] = set()
# this is the set of problems where I have the right answer but wrong solution

fails_pcc: Set[Union[str, int]] = {3, 5, 7, 10, 34, 'is_prime'}
# this is the set of tests that fail on PCC compiler
# this is because (at least on my system) including <stdlib.h> or <math.h> result in syntax errors
# for the moment that is just limited to anything that includes primes.h or digits.h


# platform variables section
IN_WINDOWS = system() == 'Windows'
IN_TERMUX = bool(which('termux-setup-storage'))

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
    warn("Test suite told to ignore slow tests AND run only slow tests. Ignoring conflicing options")

# if in Termux, default to NO_SLOW, but allow users to explicitly override that decision
NO_SLOW = ((IN_TERMUX and _parsed_NO_SLOW is None) or _parsed_NO_SLOW) and not _parsed_ONLY_SLOW
ONLY_SLOW = _parsed_ONLY_SLOW and not _parsed_NO_SLOW
NO_OPTIONAL_TESTS = (_parsed_NO_OPTIONAL_TESTS is None and ONLY_SLOW) or _parsed_NO_OPTIONAL_TESTS

# this part isn't necessary, but I like having the binaries include their compile architecture
if not (IN_WINDOWS or IN_TERMUX) and processor() and ' ' not in processor():
    EXE_EXT = processor()
elif IN_WINDOWS:
    # processor() returns something too verbose in Windows
    EXE_EXT = "x86"
    if machine().endswith('64'):
        EXE_EXT += "_64"
elif IN_TERMUX:
    # processor() doesn't seem to work on Termux
    EXE_EXT = check_output('lscpu').split()[1].decode()
else:
    warn("Could not detect system architecture, defaulting to .exe")
    EXE_EXT = "exe"

SOURCE_TEMPLATE = "{}{}p{{:0>4}}.c".format(C_FOLDER, sep)
if IN_TERMUX:
    EXE_TEMPLATE = "{}/p{{:0>4}}.{{}}.{}".format(expanduser("~"), EXE_EXT)
    # Termux can't make executable files outside of $HOME
else:
    EXE_TEMPLATE = "{}{}p{{:0>4}}.{{}}.{}".format(C_FOLDER, sep, EXE_EXT)
    # include sep in the recipe so that Windows won't complain

GCC_BINARY = environ.get('GCC_OVERRIDE', 'gcc')

# compiler variables section
compilers: List[str] = []
templates = {
    'GCC': "{} {{}} -O2 -lm -Werror -std=c11 -o {{}}".format(GCC_BINARY),
    'CLANG': "clang {} -O2 -lm -Werror -std=c11 -o {}",
    'CL': "cl -Fe:{1} -Foobjs\\ -O2 -TC {0}",
    'TCC': "tcc -lm -Werror -o {1} {0}",
    'ICC': "icc {} -O2 -lm -Werror -std=c11 -o {}",
    'PCC': "pcc -O2 -o {1} {0}",
    'AOCC': "aocc {} -O2 -lm -Werror -std=c11 -o {}",
}

if 'COMPILER_OVERRIDE' in environ:
    compilers.extend(environ['COMPILER_OVERRIDE'].upper().split(','))
else:
    if not (IN_TERMUX and GCC_BINARY == 'gcc') and which(GCC_BINARY):  # Termux maps gcc->clang
        compilers.append('GCC')
    if which('cl'):
        @register
        def cleanup_objs():
            try:
                rmtree('objs')  # only present with cl compiler
            except Exception:
                pass  # if in multiprocess, this race-conditions

        makedirs('objs', exist_ok=True)
        compilers.append('CL')
    for x in ('aocc', 'clang', 'icc', 'pcc', 'tcc'):
        if which(x):
            compilers.append(x.upper())
if not compilers:
    raise RuntimeError("No compilers detected!")


@fixture(params=sorted(compilers))
def compiler(request):  # type: ignore
    return request.param


# to make sure the benchmarks sort correctly
@fixture(params=("{:03}".format(x) for x in sorted(answers)))
def key(request):  # type: ignore
    return int(request.param)  # reduce casting burden on test


def test_compiler_macros(compiler):
    if NO_OPTIONAL_TESTS:
        skip()
    exename = EXE_TEMPLATE.format("test_compiler_macros", compiler)
    test_path = Path(__file__).parent.joinpath("tests", "test_compiler_macros.c")
    try:
        check_call(templates[compiler].format(test_path, exename).split())
        buff = check_output([exename])
        is_CL, is_CLANG, is_GCC, is_INTEL, is_AMD, is_PCC, is_TCC = (int(x) for x in buff.split())
        assert bool(is_CL) == (compiler == "CL")
        assert bool(is_CLANG) == (compiler == "CLANG")
        assert bool(is_GCC) == (compiler == "GCC")
        assert bool(is_INTEL) == (compiler == "ICC")
        assert bool(is_AMD) == (compiler == "AOCC")
        assert bool(is_PCC) == (compiler == "PCC")
        assert bool(is_TCC) == (compiler == "TCC")
    finally:
        try:
            remove(exename)
        except Exception:
            warn("EXE may not have been deleted")


def test_is_prime(benchmark, compiler):
    if NO_OPTIONAL_TESTS or ONLY_SLOW:
        skip()
    from p0007 import is_prime, prime_factors, primes

    MAX_PRIME = 1_000_000
    exename = EXE_TEMPLATE.format("test_is_prime", compiler)
    test_path = Path(__file__).parent.joinpath("tests", "test_is_prime.c")
    args = templates[compiler].format(test_path, exename) + " -DMAX_PRIME={}".format(MAX_PRIME)
    try:
        check_call(args.split())
        with TemporaryFile('wb+') as f:
            run_test = partial(check_call, [exename], stdout=f)
            benchmark.pedantic(run_test, iterations=1, rounds=1)
            prime_cache = tuple(primes(MAX_PRIME))
            for line in f.readlines():
                num, prime, composite, idx = (int(x) for x in line.split())
                assert bool(prime) == bool(is_prime(num))
                assert bool(composite) == (not is_prime(num))
                assert composite == next(iter(prime_factors(num)))
                assert idx == -1 or prime_cache[idx] == num

        # sometimes benchmark disables itself, so check for .stats
        if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 200 * MAX_PRIME // 1000000:
            fail("Exceeding 200ns average!")
    except CalledProcessError:
        if compiler == 'PCC' and 'is_prime' in fails_pcc:
            xfail("Including <math.h> or <stdlib.h> on PCC seems to yield syntax errors")
        raise
    else:
        if compiler == 'PCC' and 'is_prime' in fails_pcc:
            fail("This test is expected to fail, yet it didn't!")
    finally:
        try:
            remove(exename)
        except Exception:
            warn("EXE may not have been deleted")


def test_problem(benchmark, key, compiler):
    if (NO_SLOW and key in known_slow) or (ONLY_SLOW and key not in known_slow):
        skip()
    filename = SOURCE_TEMPLATE.format(key)
    exename = EXE_TEMPLATE.format(key, compiler)  # need to have both to keep name unique
    try:
        check_call(templates[compiler].format(filename, exename).split())
        run_test = partial(check_output, [exename])

        if key in known_slow:
            answer = benchmark.pedantic(run_test, iterations=1, rounds=1)
        else:
            answer = benchmark(run_test)
        assert answers[key] == int(answer.strip())
        # sometimes benchmark disables itself, so check for .stats
        if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 60:
            fail_func = xfail if key in known_slow else fail
            fail_func("Exceeding 60s!")
    except CalledProcessError:
        if compiler == 'PCC' and key in fails_pcc:
            xfail("Including <math.h> or <stdlib.h> on PCC seems to yield syntax errors")
        raise
    else:
        if compiler == 'PCC' and key in fails_pcc:
            fail("This test is expected to fail, yet it didn't!")
    finally:
        try:
            remove(exename)
        except Exception:
            warn("EXE may not have been deleted")

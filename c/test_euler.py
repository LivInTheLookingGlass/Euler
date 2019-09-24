from atexit import register
from functools import partial
from os import environ, makedirs, remove, sep
from os.path import expanduser
from pathlib import Path
from platform import processor, machine, system
from shutil import rmtree, which
from subprocess import check_call, check_output
from sys import path
from tempfile import TemporaryFile

from pytest import fail, fixture, skip, xfail

path.append(str(Path(__file__).parent.parent.joinpath("python")))

answers = {
    1: 233168,
    2: 4613732,
    3: 6857,
    5: 232792560,
    6: 25164150,
    7: 104743,
    10: 142913828922,
    34: 40730,
    76: 190569291,
}

known_slow = {}
# this is the set of problems where I have the right answer but wrong solution


# platform variables section
IN_WINDOWS = system() == 'Windows'
IN_TERMUX = bool(which('termux-setup-storage'))

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
    EXE_EXT = "exe"

SOURCE_TEMPLATE = "p{:04}.c"
if IN_TERMUX:
    EXE_TEMPLATE = "{}/p{{:0>4}}.{{}}.{}".format(expanduser("~"), EXE_EXT)
    # Termux can't make executable files outside of $HOME
else:
    EXE_TEMPLATE = ".{}p{{:0>4}}.{{}}.{}".format(sep, EXE_EXT)
    # include sep in the recipe so that Windows won't complain

# compiler variables section
compilers = []
templates = {
    'GCC': "{} {{}} -O2 -lm -Werror -std=c11 -o {{}}".format(environ.get('GCC_OVERRIDE', 'gcc')),
    'CLANG': "clang {} -O2 -lm -Werror -std=c11 -o {}",
    'CL': "cl -Fe:{1} -Foobjs\\ -O2 -TC {0}",
    'TCC': "tcc -lm -Werror -o {1} {0}",
}

if 'COMPILER_OVERRIDE' in environ:
    compilers.extend(environ['COMPILER_OVERRIDE'].upper().split(','))
else:
    if not IN_TERMUX and which('gcc'):  # Termux maps gcc->clang
        compilers.append('GCC')
    if which('clang'):
        compilers.append('CLANG')
    if which('cl'):
        @register
        def cleanup_objs():
            try:
                rmtree('objs')  # only present with cl compiler
            except Exception:
                pass  # if in multiprocess, this race-conditions

        makedirs('objs', exist_ok=True)
        compilers.append('CL')
    if which('pcc'):
        raise NotImplementedError()
    if which('tcc'):
        compilers.append('TCC')
    if which('icc'):
        raise NotImplementedError()
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
    exename = EXE_TEMPLATE.format("test_compiler_macros", compiler)
    test_path = Path(__file__).parent.joinpath("tests", "test_compiler_macros.c")
    try:
        check_call(templates[compiler].format(test_path, exename).split())
        buff = check_output([exename])
        is_CL, is_CLANG, is_GCC, is_INTEL, is_TCC = (int(x) for x in buff.split())
        assert bool(is_CL) == (compiler == "CL")
        assert bool(is_CLANG) == (compiler == "CLANG")
        assert bool(is_GCC) == (compiler == "GCC")
        assert bool(is_INTEL) == (compiler == "ICC")
        assert bool(is_TCC) == (compiler == "TCC")
    finally:
        try:
            remove(exename)
        except Exception:
            pass  # might not have been made yet


def test_is_prime(benchmark, compiler):
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
        if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 200 * MAX_PRIME // 1_000_000:
            fail("Exceeding 200ns average!")
    finally:
        try:
            remove(exename)
        except Exception:
            pass  # might not have been made yet


def test_problem(benchmark, key, compiler):
    if IN_TERMUX and key in known_slow:
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
            if key in known_slow:
                xfail("Exceeding 60s!")
            else:
                fail("Exceeding 60s!")
    finally:
        try:
            remove(exename)
        except Exception:
            pass  # might not have been made yet

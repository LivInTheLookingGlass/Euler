from atexit import register
from functools import partial
from os import makedirs, remove, sep
from os.path import expanduser
from platform import processor, machine, system
from shutil import rmtree, which
from subprocess import check_call, check_output

from pytest import fail, fixture, skip

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
    EXE_TEMPLATE = "{}/p{{:04}}.{{}}.{}".format(expanduser("~"), EXE_EXT)
    # Termux can't make executable files outside of $HOME
else:
    EXE_TEMPLATE = ".{}p{{:04}}.{{}}.{}".format(sep, EXE_EXT)
    # include sep in the recipe so that Windows won't complain

# compiler variables section
compilers = []
templates = {
    'GCC': "gcc {} -O2 -lm -Werror -std=c11 -o {}",
    'CLANG': "clang {} -O2 -lm -Werror -std=c11 -o {}",
    'CL': "cl -Fe:{1} -Foobjs\\ -O2 -TC {0}",
}

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
    raise NotImplementedError()
if which('icc'):
    raise NotImplementedError()
if not compilers:
    raise RuntimeError("No compilers detected!")


@fixture(params=compilers)
def compiler(request):  # type: ignore
    return request.param


# to make sure the benchmarks sort correctly
@fixture(params=("{:03}".format(x) for x in sorted(answers)))
def key(request):  # type: ignore
    return int(request.param)  # reduce casting burden on test


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
            fail("Exceeding 60s!")
    finally:
        try:
            remove(exename)
        except Exception:
            pass  # might not have been made yet

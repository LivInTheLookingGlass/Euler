from functools import partial
from os import remove, sep
from os.path import expanduser
from platform import processor, machine, system
from shutil import which
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
    EXE_EXT = check_output('lscpu').split()[1]
else:
    EXE_EXT = "exe"

if IN_TERMUX:
    EXE_TEMPLATE = "{}/p{{}}.{}".format(expanduser("~"), EXE_EXT)
    # Termux can't make executable files outside of $HOME
else:
    EXE_TEMPLATE = ".{}p{{}}.{}".format(sep, EXE_EXT)
    # include sep in the recipe so that Windows won't complain

# compiler variables section
USING_CL = False
USING_GCC = False
USING_CLANG = False

if which('gcc'):
    COMPILER_TEMPLATE = "gcc {} -O -lm -Werror -std=c11 -o {}"
    USING_GCC = True
elif which('clang'):
    COMPILER_TEMPLATE = "clang {} -O -lm -Werror -std=c11 -o {}"
    USING_CLANG = True
elif IN_WINDOWS and which('cl'):
    COMPILER_TEMPLATE = "cl /Fe:{1} /O2 /TC {0}"
    USING_CL = True
else:
    raise RuntimeError("Unsupported system!")


# to make sure the benchmarks sort correctly
@fixture(params=("{:04}".format(x) for x in sorted(answers)))
def key(request):  # type: ignore
    return request.param


def test_problem(benchmark, key):
    key_i = int(key)
    filename = "p{}.c".format(key)
    exename = EXE_TEMPLATE.format(key)
    try:
        check_call(COMPILER_TEMPLATE.format(filename, exename).split())
        run_test = partial(check_output, [exename])

        if key_i in known_slow:
            if IN_TERMUX:
                skip()
            assert answers[key_i] == int(benchmark.pedantic(
                run_test, iterations=1, rounds=1
            ).strip())
        else:
            assert answers[key_i] == int(benchmark(run_test).strip())
        # sometimes benchmark disables itself, so check for .stats
        if hasattr(benchmark, 'stats') and benchmark.stats.stats.max > 60:
            fail("Exceeding 60s!")
    finally:
        try:
            remove(exename)
        except Exception:
            pass  # might not have been made yet
        if USING_CL:
            try:
                remove("p{}.obj".format(key))  # only present with cl compiler
            except Exception:
                pass  # might not have been made yet

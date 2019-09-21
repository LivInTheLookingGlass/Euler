LINT?=
PY?=python3
PROXY?=
USER_FLAG?=--user
PIP?=$(PY) -m pip

ifeq ($(pyver),pypy3)
LINT=less  # mypy seemingly not supported on Travis pypy
endif

ifeq ($(LINT),false)
pytest_args?= --benchmark-min-time=0.05 --benchmark-sort=fullname
else
ifeq ($(LINT),true)
pytest_args?= --mypy --mypy-ignore-missing-imports --flake8 --isort -k 'not test_problem and not test_is_prime'
else
ifeq ($(LINT),less)
pytest_args?= --flake8 --isort --benchmark-min-time=0.05 --benchmark-sort=fullname
else
pytest_args?= --mypy --mypy-ignore-missing-imports --flake8 --isort --benchmark-min-time=0.05 --benchmark-sort=fullname
endif
endif
endif

ifneq ($(PROXY), )
PROXY_ARG="--proxy=$(PROXY)"
else
PROXY_ARG=
endif

test: dependencies _test

test_%:
	$(MAKE) test pytest_args="$(pytest_args) -n$*" PY=$(PY) PROXY=$(PROXY)

_test:
	$(PY) -m pytest -v $(pytest_args)

ifneq ($(pyver),pypy3)
dependencies:
	$(PIP) install -r requirements.txt $(USER_FLAG) $(PROXY_ARG)
else
dependencies:
	cat requirements.txt | grep -v "mypy" > .requirements.txt
	$(PIP) install -r .requirements.txt $(USER_FLAG) $(PROXY_ARG)
endif
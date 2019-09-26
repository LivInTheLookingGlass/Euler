LINT?=
PY?=python3
PROXY?=
USER_FLAG?=--user
PIP?=$(PY) -m pip
MYPY?=true

ifneq ($(MYPY),true)
LINT=less
endif

ifeq ($(LINT),false)
pytest_args?= -v --benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose
else
ifeq ($(LINT),true)
pytest_args?= -v --mypy --mypy-ignore-missing-imports --flake8 --isort -k 'not test_problem and not test_is_prime'
else
ifeq ($(LINT),less)
pytest_args?= -v --flake8 --isort --benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose
else
pytest_args?= -v --mypy --mypy-ignore-missing-imports --flake8 --isort --benchmark-min-time=0.05 --benchmark-group-by=fullfunc --benchmark-sort=fullname --benchmark-verbose
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
	$(MAKE) test pytest_args="$(pytest_args) -n$*" $(MFLAGS)

_test:
	$(PY) -m pytest $(pytest_args)

ifeq ($(MYPY),true)
dependencies:
	$(PIP) install -r requirements.txt $(USER_FLAG) $(PROXY_ARG)
else
dependencies:
	cat requirements.txt | grep -v "mypy" > .requirements.txt
	$(PIP) install -r .requirements.txt $(USER_FLAG) $(PROXY_ARG)
endif

LINT?=
PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
MYPY?=true
COV?=false

ifneq ($(MYPY),true)
LINT=less
endif

ifeq ($(LINT),false)
pytest_args?= -vl --benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose
else
ifeq ($(LINT),true)
pytest_args?= -vl --mypy --mypy-ignore-missing-imports --isort -k 'not test_problem and not test_is_prime and not test_groupwise'
else
ifeq ($(LINT),less)
pytest_args?= -vl --isort --benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose
else
pytest_args?= -vl --mypy --mypy-ignore-missing-imports --isort --benchmark-min-time=0.05 --benchmark-group-by=fullfunc --benchmark-sort=fullname --benchmark-verbose
endif
endif
endif

ifeq ($(COV),true)
pytest_args+= --cov
endif

ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else
ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
else
PROXY_ARG=
endif
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

clean:
	rm -r ./{*,*/*}{.pyc,__pycache__,.mypy_cache} || echo

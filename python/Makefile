LINT?=
PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
MYPY?=true
COV?=false

ifneq ($(MYPY),true)
LINT=less
endif

benchmark_flags=--benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose

ifeq ($(LINT),false)
pytest_args?= -vl
else
ifeq ($(LINT),true)
pytest_args?= -vl --mypy --mypy-ignore-missing-imports --isort -k 'not test_problem and not test_is_prime and not test_groupwise'
else
ifeq ($(LINT),less)
pytest_args?= -vl --isort
else
pytest_args?= -vl --mypy --mypy-ignore-missing-imports --isort
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
	$(PY) -m pytest $(pytest_args) $(benchmark_flags)

test_%: dependencies
	$(PY) -m pytest $(pytest_args) -n$*

_test:

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

pytest_args?= --mypy --mypy-ignore-missing-imports --flake8 --isort --benchmark-min-time=0.05 --benchmark-sort=fullname
PY?=python3
PROXY?=
USER?=--user
PIP?=$(PY) -m pip

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

dependencies:
	$(PIP) install -r requirements.txt $(USER) $(PROXY_ARG)

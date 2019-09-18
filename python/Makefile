pytest_args?= --mypy --mypy-ignore-missing-imports --flake8 --isort --benchmark-min-time=0.05 --benchmark-sort=fullname
PY?=python3
PROXY?=

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
	$(PY) -m pip install -r requirements.txt --user $(PROXY_ARG)

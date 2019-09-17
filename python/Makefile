pytest_args?= --mypy --mypy-ignore-missing-imports --flake8 --isort
PY?=python3
PROXY?=

test: dependencies _test

test_%:
	$(MAKE) test pytest_args="$(pytest_args) -n$*" PY=$(PY) PROXY=$(PROXY)

_test:
	$(PY) -m pytest -v --benchmark-sort=fullname $(pytest_args)

dependencies:
	$(PY) -m pip install -r requirements.txt --user $(PROXY)

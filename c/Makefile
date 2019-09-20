
PY?=python3
PROXY?=

ifneq ($(PROXY), )
PROXY_ARG="--proxy=$(PROXY)"
else
PROXY_ARG=
endif

test_%: dependencies
	$(PY) -m pytest -v -n$* test_euler.py

test: dependencies
	$(PY) -m pytest -v --benchmark-sort=fullname test_euler.py

dependencies:
	$(PY) -m pip install -r requirements.txt --user $(PROXY_ARG)

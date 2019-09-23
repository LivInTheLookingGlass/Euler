
PY?=python3
PROXY?=
USER_FLAG?=--user
PIP?=$(PY) -m pip

ifneq ($(PROXY), )
PROXY_ARG="--proxy=$(PROXY)"
else
PROXY_ARG=
endif

test_%: dependencies
	$(PY) -m pytest -v -n$* test_euler.py

test: dependencies
	$(PY) -m pytest -v --benchmark-sort=fullname --benchmark-verbose test_euler.py

dependencies:
	$(PIP) install -r requirements.txt $(USER_FLAG) $(PROXY_ARG)

lint:
	clang-tidy *.c # -warnings-as-errors=*

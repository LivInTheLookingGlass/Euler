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
	$(PY) -m pytest -v --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose test_euler.py

dependencies:
	$(PIP) install -r requirements.txt $(USER_FLAG) $(PROXY_ARG)

lint:
	if test -z "$(clang-tidy p0000_template.c -warnings-as-errors=* 2>&1 | grep "Unknown command line argument")"; then \
		clang-tidy *.c -warnings-as-errors=*; \
	else \
		clang-tidy *.c; \
	fi

PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip

ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else
ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
else
PROXY_ARG=
endif
endif

test_%: dependencies
	cd ../python; $(MAKE) dependencies $(MFLAGS)
	$(PY) -m pytest -vl -n$* test_euler.py --cov

test: dependencies
	$(PY) -m pytest -vl --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose test_euler.py --cov

dependencies:
	git submodule init
	git submodule update
	$(PIP) install -r requirements.txt $(USER_FLAG) $(PROXY_ARG)

lint:
	if test -z "$(clang-tidy p0000_template.c -warnings-as-errors=* 2>&1 | grep "Unknown command line argument")"; then \
		clang-tidy *.c -warnings-as-errors=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling; \
	else \
		clang-tidy *.c; \
	fi

native:
	$(CC) test.c Unity/src/unity.c -O2 -lm -Wall -Werror -std=c11 -march=native -flto -DAMD_COMPILER=0

clean:
	rm -r build ./{*,*/*}{.pyc,__pycache__,.mypy_cache} || echo

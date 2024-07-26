PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
BLUE=\033[0;34m
NC=\033[0m  # No Color

ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else
ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
else
PROXY_ARG=
endif
endif

help:
	@echo "  $(BLUE)test$(NC)  	run through all tests in sequence. Utilizes the Python test runner infrastructure"
	@echo "  $(BLUE)test_*$(NC)	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the Python test runner infrastructure"
	@echo "  $(BLUE)dependencies$(NC)	initialize submodules and install any Python dependencies"
	@echo "  $(BLUE)lint$(NC)  	run clang-tidy across each of the .c and .h files"
	@echo "  $(BLUE)native$(NC) 	build a test binary utilizing the Unity test framework"
	@echo "  $(BLUE)clean$(NC) 	clean up any stray files"

test_%: dependencies
	cd ../python; $(MAKE) dependencies $(MFLAGS)
	$(PY) -m pytest -vl -n$* test_euler.py

test: dependencies
	$(PY) -m pytest -vl --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose test_euler.py

dependencies:
	git submodule init
	git submodule update
	$(PIP) install -r requirements.txt -r ../python/requirements.txt $(USER_FLAG) $(PROXY_ARG)

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

PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
BLUE=\033[0;34m
NC=\033[0m # No Color

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
	@echo "  $(BLUE)lint$(NC)  	run clang-tidy across each of the .cpp and .h files"
	@echo "  $(BLUE)clean$(NC) 	clean up any stray files"

test_%: dependencies
	cd ../python; $(MAKE) dependencies $(MFLAGS)
	$(PY) -m pytest -vl -n$* test_euler.py --cov

test: dependencies
	$(PY) -m pytest -vl --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose test_euler.py

dependencies:
	$(PIP) install -r requirements.txt -r ../python/requirements.txt $(USER_FLAG) $(PROXY_ARG)

lint:
	if test -z "$(clang-tidy p0000_template.cpp -warnings-as-errors=* 2>&1 | grep "Unknown command line argument")"; then \
		clang-tidy *.cpp -warnings-as-errors=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling; \
	else \
		clang-tidy *.cpp; \
	fi

native:
	$(CXX) test.cpp ./Unity/src/unity.c -O2 -lm -Wall -Werror -std=c++11 -march=native -flto -DAMD_COMPILER=0 -Wno-deprecated

clean:
	rm -r build ./{*,*/*}{.pyc,__pycache__,.mypy_cache} || echo

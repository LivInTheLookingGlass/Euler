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

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)  	run through all tests in sequence. Utilizes the Python test runner infrastructure"
	@echo "  $(BLUE)test_*$(NC)	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the Python test runner infrastructure"
	@echo "  $(BLUE)dependencies$(NC)	initialize submodules and install any Python dependencies"
	@echo "  $(BLUE)lint$(NC)  	run clang-tidy across each of the .cpp and .h files"
	@echo "  $(BLUE)clean$(NC) 	clean up any stray files"

.PHONY: test_%
test_%: ../LICENSE dependencies
	@$(PY) -m pytest -dvl -n$* test_euler.py --cov

.PHONY: test
test: ../LICENSE dependencies
	@$(PY) -m pytest -vl --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose test_euler.py --cov

Unity/src/unity.c:
	@git submodule init
	@git submodule update

.PHONY: dependencies
dependencies: Unity
	@$(MAKE) -C ../python dependencies $(MFLAGS)
	@$(PIP) install -r requirements.txt -r ../python/requirements.txt $(USER_FLAG) $(PROXY_ARG)

.PHONY: lint
lint:
	@if test -z "$(clang-tidy src/p0000_template.cpp -warnings-as-errors=* 2>&1 | grep "Unknown command line argument")"; then \
		clang-tidy src/*.cpp -warnings-as-errors=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling; \
	else \
		clang-tidy src/*.cpp; \
	fi

.PHONY: native
native: ../LICENSE Unity/src/unity.c
	@$(CXX) test.cpp Unity/src/unity.c -O2 -lm -Wall -Werror -std=c++11 -march=native -flto -DAMD_COMPILER=0 -Wno-deprecated

.PHONY: clean
clean:
	@rm -rf build {.,*,*/*}/{*.pyc,__pycache__,.mypy_cache,.pytest_cache,.benchmarks} || echo

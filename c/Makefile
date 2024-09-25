PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
BLUE=\033[0;34m
NC=\033[0m # No Color
O?=2
COV?=false

ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else
ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
else
PROXY_ARG=
endif
endif

pytest_args= -vl --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose
ifneq ($(COV),false)
pytest_args+= --cov
endif

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)  	run through all tests in sequence. Utilizes the Python test runner infrastructure"
	@echo "  $(BLUE)test_*$(NC)	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the Python test runner infrastructure"
	@echo "  $(BLUE)dependencies$(NC)	initialize submodules and install any Python dependencies"
	@echo "  $(BLUE)lint$(NC)  	run clang-tidy across each of the .c and .h files"
	@echo "  $(BLUE)native$(NC) 	build a test binary utilizing the Unity test framework"
	@echo "  $(BLUE)clean$(NC) 	clean up any stray files"

.PHONY: test_%
test_%: ../LICENSE dependencies
	@$(PY) -m pytest $(pytest_args) -d -n$* test_euler.py

.PHONY: test
test: ../LICENSE dependencies
	@$(PY) -m pytest $(pytest_args) test_euler.py

Unity/src/unity.c:
	@git submodule init
	@git submodule update

.PHONY: dependencies
dependencies: Unity/src/unity.c
	@$(MAKE) -C ../python dependencies $(MFLAGS)
	@$(PIP) install -r requirements.txt -r ../python/requirements.txt $(USER_FLAG) $(PROXY_ARG)

.PHONY: lint
lint:
	@if test -z "$(clang-tidy src/p0000_template.c -warnings-as-errors=* 2>&1 | grep "Unknown command line argument")"; then \
		clang-tidy src/*.c -warnings-as-errors=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling; \
	else \
		clang-tidy src/*.c; \
	fi

.PHONY: native
native: ../LICENSE Unity/src/unity.c
	@$(CC) test.c Unity/src/unity.c -O$(O) -g -lm -lc -Wall -Werror -std=gnu99 -march=native -flto --coverage -o native_test_runner

.PHONY: native_test
native_test: native
	@./native_test_runner

.PHONY: clean
clean: SHELL := bash
clean:
	@rm -rf build dist {.,*,*/*{,/*}}/{*.pyc,__pycache__,.mypy_cache,.pytest_cache,.benchmarks} || echo

dist/c-lib.wasm: build/lib.c
	@mkdir -p dist
	@emcc build/lib.c -Wl,--whole-archive -DUNITY_END -O$(O) -s EXPORTED_RUNTIME_METHODS="['ccall']" -o dist/c-lib.mjs

build/lib.c: ../LICENSE
	@mkdir -p build
	@> build/lib.c
	@for file in src/p*.c; do \
		if [ -f "$$file" ]; then \
			echo "#include \"../$$file\"" >> build/lib.c; \
		fi \
	done

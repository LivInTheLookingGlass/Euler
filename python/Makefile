LINT?=
PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
MYPY?=true
COV?=false

ifneq ($(MYPY),true)
LINT=less
endif

benchmark_flags=--benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose

ifeq ($(LINT),false)
pytest_args?= -vl
else
ifeq ($(LINT),true)
pytest_args?= -vl --mypy --mypy-ignore-missing-imports --isort --flake8 -k 'not test_problem and not test_is_prime and not test_groupwise'
else
ifeq ($(LINT),less)
pytest_args?= -vl --isort
else
pytest_args?= -vl --mypy --mypy-ignore-missing-imports --isort --flake8
endif
endif
endif

ifeq ($(COV),true)
pytest_args+= --cov
endif

ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else
ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
else
PROXY_ARG=
endif
endif
BLUE=\033[0;34m
NC=\033[0m # No Color

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	run through all tests in sequence. Utilizes the pytest test runner infrastructure"
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the pytest runner"
	@echo "  $(BLUE)dependencies$(NC)	grabs all dependencies through pip"
	@echo "  $(BLUE)clean$(NC)  	clean up any stray files"

.PHONY: test
test: ../LICENSE dependencies
	$(PY) -m pytest $(pytest_args) $(benchmark_flags)

.PHONY: test_%
test_%: ../LICENSE dependencies
	$(PY) -m pytest $(pytest_args) -d -n$*

.PHONY: dependencies
ifeq ($(MYPY),true)
dependencies:
	$(PIP) install -r requirements.txt $(USER_FLAG) $(PROXY_ARG)
else
dependencies:
	cat requirements.txt | grep -v "mypy" > .requirements.txt
	$(PIP) install -r .requirements.txt $(USER_FLAG) $(PROXY_ARG)
endif

.PHONY: clean
clean:
	rm -r ./{*,*/*}{.pyc,__pycache__,.mypy_cache} || echo

.PHONY: webpack
webpack: ../LICENSE
	# Create temporary directory for the archive content
	mkdir -p ../docs/_static/dist/tmp/euler
	cp -r ../_data ../docs/_static/dist/tmp/euler/_data
	cp -r ../python ../docs/_static/dist/tmp/euler/python

	# Add __init__.py files to the temporary directory
	echo "# init file" > ../docs/_static/dist/tmp/euler/__init__.py
	echo "# init file" > ../docs/_static/dist/tmp/euler/python/__init__.py

	# Exclude unwanted directories and create tarball
	cd ../docs/_static/dist/tmp && \
		tar --exclude='__pycache__' --exclude='*/__pycache__' \
			-czvf ../python.tar.gz euler

	# Clean up temporary directory
	rm -rf ../docs/_static/dist/tmp

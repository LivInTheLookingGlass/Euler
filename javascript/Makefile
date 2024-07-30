NOT_TERMUX?=$(shell command -v termux-setup-storage > /dev/null 2>&1 ; echo $$?)
HAS_NPM?=$(shell command -v npm > /dev/null 2>&1 ; echo $$?)
COV?=false

ifeq ($(COV),true)
MOCHA=istanbul cover ./node_modules/mocha/bin/_mocha
else
MOCHA=npx mocha
endif
BLUE=\033[0;34m
NC=\033[0m # No Color

help:
	@echo "  $(BLUE)test$(NC)   	run through all tests in sequence. Utilizes the Mocha test runner"
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the Mocha test runner"
	@echo "  $(BLUE)dependencies$(NC)	runs npm install"
	@echo "  $(BLUE)lint$(NC)   	runs eslint"
	@echo "  $(BLUE)bun_test$(NC)   	run through all tests in sequence. Utilizes the bun runtime and test runner"
	@echo "  $(BLUE)bun_dependencies$(NC)	installs bun and runs bun install"
	@echo "  $(BLUE)webpack$(NC)	Packages these tests for use in browsers"
	@echo "  $(BLUE)clean$(NC)  	clean up any stray files"

test: dependencies
	$(MOCHA) euler.test.js

test_auto: dependencies
	$(MOCHA) --parallel euler.test.js

test_%: dependencies
	$(MOCHA) --parallel -j $* euler.test.js

bun_dependencies:
	if ! command -v bun; then npm -g install bun; fi
	bun install

bun_test: bun_dependencies
ifeq ($(COV),true)
	bun test --coverage --coverage-reporter lcov
else
	bun test
endif

ifneq ($(HAS_NPM),0)
ifeq ($(OS),Windows_NT)  # if no NPM and Windows
dependencies:
	1>&2 echo "Windows not yet supported"
	exit /b -1
else
ifeq ($(NOT_TERMUX),0)  # if no NPM and Termux
dependencies:
	pkg install -y nodejs;
	$(MAKE) _dependencies $(MFLAGS)
else  # if no NPM and not Termux
dependencies:
	curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.34.0/install.sh | bash \
	export NVM_DIR="$$HOME/.nvm"; \
	[ -s "$$NVM_DIR/nvm.sh" ] && \. "$$NVM_DIR/nvm.sh" \
	nvm install --lts
	$(MAKE) _dependencies $(MFLAGS)
endif
endif
else  # has NPM
dependencies: _dependencies
endif

_dependencies:
ifeq ($(COV),true)
	npm install -g istanbul
endif
	npm install --include=dev

lint: dependencies
	npx eslint *.js src/*.js src/lib/*.js --ignore-pattern "dist/*"

clean:
	rm -r node_modules dist || echo

webpack: dependencies
	npx webpack

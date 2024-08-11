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

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	run through all tests in sequence. Utilizes the Mocha test runner"
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the Mocha test runner"
	@echo "  $(BLUE)dependencies$(NC)	runs npm install"
	@echo "  $(BLUE)lint$(NC)   	runs eslint"
	@echo "  $(BLUE)bun_test$(NC)   	run through all tests in sequence. Utilizes the bun runtime and test runner"
	@echo "  $(BLUE)bun_dependencies$(NC)	installs bun and runs bun install"
	@echo "  $(BLUE)webpack$(NC)	Packages these tests for use in browsers"
	@echo "  $(BLUE)clean$(NC)  	clean up any stray files"

.PHONY: test
test: ../LICENSE dependencies bun_test
	@$(MOCHA) euler.test.js

test_auto:../LICENSE  dependencies bun_test
	@$(MOCHA) --parallel euler.test.js

.PHONY: test_%
test_%: ../LICENSE dependencies bun_test
	@$(MOCHA) --parallel -j $* euler.test.js

.PHONY: bun_dependencies
bun_dependencies:
ifeq ($(NOT_TERMUX),1)
ifneq ($(HAS_NPM),0)
	@if ! command -v bun; then npm -g install bun; fi
endif
	@bun install
endif

.PHONY: bun_test
bun_test: ../LICENSE bun_dependencies
ifeq ($(NOT_TERMUX),1)
ifeq ($(COV),true)
	@bun test --coverage --coverage-reporter lcov
else
	@bun test
endif
endif

.PHONY: dependencies
ifneq ($(HAS_NPM),0)
ifeq ($(OS),Windows_NT)  # if no NPM and Windows
dependencies:
	@1>&2 echo "Windows not yet supported"
	@exit /b -1
else
ifeq ($(NOT_TERMUX),0)  # if no NPM and Termux
dependencies:
	@pkg install -y nodejs;
	@$(MAKE) node_modules/chai/LICENSE $(MFLAGS) --no-print-directory
else  # if no NPM and not Termux
dependencies:
	@curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.34.0/install.sh | bash \
	@export NVM_DIR="$$HOME/.nvm"; \
	@[ -s "$$NVM_DIR/nvm.sh" ] && \. "$$NVM_DIR/nvm.sh" \
	@nvm install --lts
	@$(MAKE) node_modules/chai/LICENSE $(MFLAGS) --no-print-directory
endif
endif
else  # has NPM
dependencies: node_modules/chai/LICENSE
endif

node_modules/chai/LICENSE:
ifeq ($(COV),true)
	@npm install -g istanbul
endif
	@npm install --include=dev

.PHONY: lint
lint: dependencies
	@npx eslint *.js src/*.js src/lib/*.js --ignore-pattern "dist/*"

.PHONY: clean
clean:
	@rm -rf node_modules dist src/lib/fallbacks || echo

.PHONY: webpack
webpack: ../LICENSE dependencies
	@mkdir -p src/lib/fallbacks
	@for f in ../_data/*; do \
	  bf=$$(echo $$f | sed "s/.*\///"); \
	  echo -n "exports.value = '" > ./src/lib/fallbacks/$$bf.js; \
	  base64 -w0 $$f | head --bytes -1 >> ./src/lib/fallbacks/$$bf.js; \
	  echo "';" >> ./src/lib/fallbacks/$$bf.js; \
	done
	@npx webpack

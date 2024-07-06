NOT_TERMUX?=$(shell command -v termux-setup-storage > /dev/null 2>&1 ; echo $$?)
HAS_NPM?=$(shell command -v npm > /dev/null 2>&1 ; echo $$?)
COV?=false

ifeq ($(COV),true)
MOCHA=istanbul cover ./node_modules/mocha/bin/_mocha
else
MOCHA=npx mocha
endif

test: dependencies
	$(MOCHA)

test_auto: dependencies
	$(MOCHA) --parallel

test_%: dependencies
	$(MOCHA) --parallel -j $*

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
	npm install

lint:
	npx eslint *.js

clean:
	rm -r node_modules || echo

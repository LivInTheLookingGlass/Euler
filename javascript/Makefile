test: dependencies
	npx mocha

test_%: dependencies
	echo "WARNING: multithreaded tests not supported on javascript"
	npx mocha

ifeq ($(OS),Windows_NT)
dependencies:
	1>&2 echo "Windows not yet supported"
	exit /b -1
else
dependencies:
	if command -v npm ; then \
		echo "No need to install nvm"; \
	elif command -v termux-setup-storage ; then \
		pkg install -y nodejs; \
	else \
		curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.34.0/install.sh | bash \
		export NVM_DIR="$$HOME/.nvm"; \
		[ -s "$$NVM_DIR/nvm.sh" ] && \. "$$NVM_DIR/nvm.sh \
		nvm install --lts \
	fi
	if command -v termux-setup-storage ; then \
		npm install -g \
	else \
		npm install \
	fi
endif


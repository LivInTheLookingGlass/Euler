test: dependencies
	npx mocha

test_%: dependencies
	echo "WARNING: multithreaded tests not supported on javascript"
	npx mocha

dependencies:
	@if command -v npm ; then \
		echo "No need to install nvm"; \
	else																					# if I don't have NPM \
		curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.34.0/install.sh | bash; 		# set up node version manager \
		export NVM_DIR="$$HOME/.nvm"; \
		[ -s "$$NVM_DIR/nvm.sh" ] && \. "$$NVM_DIR/nvm.sh"; 									# load it into my environment \
		nvm install --lts; 																		# install node/npm \
	fi
	@if command -v termux-setup-storage ; then 												# if I'm on termux \
		npm install -g; 																		# install packages globally \
	else																					# if I'm not on termux \
		npm install;																			# install packages locally \
	fi

# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?= -j auto
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build
PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else
ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
else
PROXY_ARG=
endif
endif

# Put it first so that "make" without argument is like "make help".
.PHONY: help
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: clean
clean:
	@rm -rf _build _static/dist || echo

.PHONY: dependencies
dependencies:
	@$(PIP) install -r requirements.txt -r ../c/requirements.txt -r ../python/requirements.txt --upgrade $(USER_FLAG) $(PROXY_ARG)
	@npm install -g jsdoc

_static/dist/bundle.js:
	@cd ../javascript && $(MAKE) webpack $(MFLAGS)
	@mkdir -p _static/dist
	@cp ../javascript/dist/bundle-js.js _static/dist/bundle-js.js

_static/dist/python.tar.gz:
	@cd ../python && $(MAKE) webpack $(MFLAGS)

.PHONY: html
html: _static/dist/bundle.js _static/dist/python.tar.gz
	@$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%:
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

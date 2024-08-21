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
	@rm -rf _build _static/dist _tags || echo

.PHONY: dependencies
dependencies: SHELL := bash
dependencies:
	@$(PIP) install --requirement={.,../{c,cplusplus,python}}/requirements.txt --upgrade $(USER_FLAG) $(PROXY_ARG)
	@npm install -g jsdoc

_static/dist/bundle.js:
	@$(MAKE) -C ../javascript webpack $(MFLAGS)
	@mkdir -p _static/dist
	@cp ../javascript/dist/bundle-js.js _static/dist/bundle-js.js

_static/dist/c-lib.js:
	@$(MAKE) -C ../c dist/lib.wasm $(MFLAGS)
	@cp ../c/dist/lib.js _static/dist/c-lib.js
	@cp ../c/dist/lib.wasm _static/dist/c-lib.wasm

_static/dist/cplusplus-lib.js:
	@$(MAKE) -C ../cplusplus dist/lib.wasm $(MFLAGS)
	@cp ../c/dist/lib.js _static/dist/cp-lib.js
	@cp ../c/dist/lib.wasm _static/dist/cp-lib.wasm

_static/dist/rust.js:
	@cd ../rust && wasm-pack build --target web --out-dir ../docs/_static/dist/

_static/dist/python.tar.gz:
	@$(MAKE) -C ../python webpack $(MFLAGS)

.PHONY: html
html:
	@$(MAKE) _static/dist/bundle.js _static/dist/c-lib.js _static/dist/cplusplus-lib.js _static/dist/python.tar.gz _static/dist/rust.js $(MFLAGS) -j
	@$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%:
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

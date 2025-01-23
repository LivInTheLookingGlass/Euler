SPHINXOPTS    ?= -j auto
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build
PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip
PROXY_ARG=

ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
endif

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
	@$(MAKE) -C ../c dist/c-lib.wasm $(MFLAGS)
	@mkdir -p _static/dist
	@cp ../c/dist/c-lib.* _static/dist/

_static/dist/cp-lib.js:
	@$(MAKE) -C ../cplusplus dist/cp-lib.wasm $(MFLAGS)
	@mkdir -p _static/dist
	@cp ../cplusplus/dist/cp-lib.* _static/dist/

_static/dist/rust.js:
	@mkdir -p _static/dist
	@cd ../rust && wasm-pack build --target web --out-dir ../docs/_static/dist/ --no-opt

_static/dist/python.tar.gz:
	@$(MAKE) -C ../python webpack $(MFLAGS)

.PHONY: html
html:
	@$(MAKE) _static/dist/bundle.js _static/dist/c-lib.js _static/dist/cp-lib.js _static/dist/python.tar.gz _static/dist/rust.js $(MFLAGS)
	@$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%:
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

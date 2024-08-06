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
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

clean:
	rm -r _build _static/test-*.html _static/dist || echo

dependencies:
	$(PIP) install -r requirements.txt -r ../c/requirements.txt -r ../python/requirements.txt --upgrade $(USER_FLAG) $(PROXY_ARG)
	npm install -g jsdoc

_static/test-c.html:
	cd ../c && $(MAKE) webpack $(MFLAGS)
	mkdir -p _static/dist
	cp ../c/dist/bundle-c.js _static/dist/bundle-c.js
	cat ../javascript/index.html | sed s#_static/bundle-js.js#_static/bundle-c.js > _static/test-c.html

_static/test-cp.html:
	cd ../cplusplus && $(MAKE) webpack $(MFLAGS)
	mkdir -p _static/dist
	cp ../cplusplus/dist/bundle-cp.js _static/dist/bundle-cp.js
	cat ../javascript/index.html | sed s#_static/bundle-js.js#_static/bundle-cp.js > _static/test-cp.html

_static/test-cs.html:
	cd ../csharp && $(MAKE) webpack $(MFLAGS)
	mkdir -p _static/dist
	cp ../csharp/dist/bundle-cs.js _static/dist/bundle-cs.js
	cat ../javascript/index.html | sed s#_static/bundle-js.js#_static/bundle-cs.js > _static/test-cs.html

_static/test-js.html:
	cd ../javascript && $(MAKE) webpack $(MFLAGS)
	mkdir -p _static/dist
	cp ../javascript/dist/bundle-js.js _static/dist/bundle-js.js
	cp ../javascript/index.html _static/test-js.html

_static/dist/pyodide.js:
	cd ../python && $(MAKE) webpack $(MFLAGS)

_static/test-rs.html:
	cd ../rust && $(MAKE) webpack $(MFLAGS)
	mkdir -p _static/dist
	cp ../rust/dist/bundle-rs.js _static/dist/bundle-rs.js
	cat ../javascript/index.html | sed s#_static/bundle-js.js#_static/bundle-rs.js > _static/test-rs.html

html: _static/test-js.html _static/dist/pyodide.js
	$(SPHINXBUILD) -M html "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%:
	$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

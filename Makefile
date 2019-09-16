PY?=python3
PROXY?=

py%:
	cd python && $(MAKE) $* PY=$(PY) PROXY=$(PROXY)

c%:
	cd c && $(MAKE) $* PY=$(PY) PROXY=$(PROXY)

js%:
	cd javascript && $(MAKE) $*

%:
	$(MAKE) c$* js$* py$* PY=$(PY)

PY?=python3

py%:
	cd python && $(MAKE) $* PY=$(PY)

c%:
	cd c && $(MAKE) $* PY=$(PY)

js%:
	cd javascript && $(MAKE) $*

%:
	$(MAKE) c$* js$* py$* PY=$(PY)

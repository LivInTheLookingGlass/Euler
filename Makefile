PY?=python3
PROXY?=

html:
	cd docs && $(make) $(MFLAGS)

py%:
	cd python && $(MAKE) $* $(MFLAGS)

cs%:
	cd csharp && $(MAKE) $* $(MFLAGS)

c%:
	cd c && $(MAKE) $* $(MFLAGS)

js%:
	cd javascript && $(MAKE) $* $(MFLAGS)

%:
	$(MAKE) c$* cs$* js$* py$* $(MFLAGS)

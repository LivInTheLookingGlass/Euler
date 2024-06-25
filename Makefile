PY?=python3
PROXY?=

py%:
	cd python && $(MAKE) $* $(MFLAGS)

c%:
	cd c && $(MAKE) $* $(MFLAGS)

cs%:
	cd csharp && $(MAKE) $* $(MFLAGS)

js%:
	cd javascript && $(MAKE) $* $(MFLAGS)

%:
	$(MAKE) c$* cs$* js$* py$* $(MFLAGS)

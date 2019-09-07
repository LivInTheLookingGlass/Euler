py%:
	cd python && $(MAKE) $*

c%:
	cd c && $(MAKE) $*

js%:
	cd javascript && $(MAKE) $*

%:
	$(MAKE) c$*
	$(MAKE) js$*
	$(MAKE) py$*

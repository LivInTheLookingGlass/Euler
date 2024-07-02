PY?=python3
PROXY?=

html dirhtml singlehtml htmlhelp qthelp devhelp epub applehelp latex man texinfo text gettext doctest linkcheck xml pseudoxml:
	cd docs && $(MAKE) $@ $(MFLAGS)

clean:
	rm -r docs/_build {c,python}/{*,*/*}.pyc csharp/*/{bin,obj,TestResults} javascript/node_modules || echo done

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

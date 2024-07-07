PY?=python3
PROXY?=

html dirhtml singlehtml htmlhelp qthelp devhelp epub applehelp latex man texinfo text gettext doctest linkcheck xml pseudoxml:
	@$(MAKE) docs_$@ $(MFLAGS)

clean: cs_clean c_clean js_clean py_clean rs_clean docs_clean

cs_%:
	@cd csharp && $(MAKE) $* $(MFLAGS)

c_%:
	@cd c && $(MAKE) $* $(MFLAGS)

docs_%:
	@cd docs && $(MAKE) $* $(MFLAGS)

js_%:
	@cd javascript && $(MAKE) $* $(MFLAGS)

py_%:
	@cd python && $(MAKE) $* $(MFLAGS)

rs_%:
	@cd rust && $(MAKE) $* $(MFLAGS)

%:
	@$(MAKE) {c,cs,js,py,rs}_$* $(MFLAGS)

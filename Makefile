PY?=python3
PROXY?=
BLUE=\033[0;34m
NC=\033[0m # No Color

help:
	@echo "This project has a number of recipes that are delegated to other Makefiles. The following jobs are available with no prefix"
	@echo "  $(BLUE)clean$(NC)"
	@echo "  $(BLUE)html$(NC)"
	@echo "  $(BLUE)dirhtml$(NC)"
	@echo "  $(BLUE)singlehtml$(NC)"
	@echo "  $(BLUE)epub$(NC)"
	@echo "  $(BLUE)latex$(NC)"
	@echo
	@echo "The following jobs are available under the docs_ prefix"
	@$(MAKE) docs_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the c_ prefix"
	@$(MAKE) c_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the cp_ prefix"
	@$(MAKE) cp_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the cs_ prefix"
	@$(MAKE) cs_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the ja_ prefix"
	@$(MAKE) ja_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the js_ prefix"
	@$(MAKE) js_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the py_ prefix"
	@$(MAKE) py_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the rs_ prefix"
	@$(MAKE) rs_help $(MFLAGS) --no-print-directory


html dirhtml singlehtml epub latex:
	@$(MAKE) docs_$@ $(MFLAGS)

clean: cs_clean cp_clean c_clean js_clean py_clean rs_clean docs_clean

cs_%:
	@cd csharp && $(MAKE) $* $(MFLAGS)

cp_%:
	@cd cplusplus && $(MAKE) $* $(MFLAGS)

c_%:
	@cd c && $(MAKE) $* $(MFLAGS)

docs_%:
	@cd docs && $(MAKE) $* $(MFLAGS)

ja_%:
	@cd java && $(MAKE) $* $(MFLAGS)

js_%:
	@cd javascript && $(MAKE) $* $(MFLAGS)

py_%:
	@cd python && $(MAKE) $* $(MFLAGS)

rs_%:
	@cd rust && $(MAKE) $* $(MFLAGS)

%:
	@$(MAKE) c_$* cp_$* cs_$* js_$* py_$* rs_$* $(MFLAGS)

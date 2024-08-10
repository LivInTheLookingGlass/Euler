PY?=python3
PROXY?=
BLUE=\033[0;34m
NC=\033[0m # No Color

.PHONY: help
help: LICENSE
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

.PHONY: html dirhtml singlehtml epub latex
html dirhtml singlehtml epub latex: LICENSE
	@$(MAKE) docs_$@ $(MFLAGS)

.PHONY: clean
clean: LICENSE cs_clean cp_clean c_clean ja_clean js_clean py_clean rs_clean docs_clean

.PHONY: cs_%
cs_%: LICENSE
	@cd csharp && $(MAKE) $* $(MFLAGS)

.PHONY: cp_%
cp_%: LICENSE
	@cd cplusplus && $(MAKE) $* $(MFLAGS)

.PHONY: c_%
c_%: LICENSE
	@cd c && $(MAKE) $* $(MFLAGS)

.PHONY: docs_%
docs_%: LICENSE
	@cd docs && $(MAKE) $* $(MFLAGS)

.PHONY: ja_%
ja_%: LICENSE
	@cd java && $(MAKE) $* $(MFLAGS)

.PHONY: js_%
js_%: LICENSE
	@cd javascript && $(MAKE) $* $(MFLAGS)

.PHONY: py_%
py_%: LICENSE
	@cd python && $(MAKE) $* $(MFLAGS)

.PHONY: rs_%
rs_%: LICENSE
	@cd rust && $(MAKE) $* $(MFLAGS)

%:
	@$(MAKE) c_$* cp_$* cs_$* ja_$* js_$* py_$* rs_$* $(MFLAGS)

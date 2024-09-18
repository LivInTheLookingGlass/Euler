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
	@echo "The following jobs are available under the fr_ prefix"
	@$(MAKE) fr_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the ja_ prefix"
	@$(MAKE) ja_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the js_ prefix"
	@$(MAKE) js_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the lu_ prefix"
	@$(MAKE) lu_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the py_ prefix"
	@$(MAKE) py_help $(MFLAGS) --no-print-directory
	@echo
	@echo "The following jobs are available under the rs_ prefix"
	@$(MAKE) rs_help $(MFLAGS) --no-print-directory

.PHONY: html dirhtml singlehtml epub latex
html dirhtml singlehtml epub latex: LICENSE
	@$(MAKE) docs_$@ $(MFLAGS) --no-print-directory

.PHONY: clean
clean:
	@$(MAKE) cs_clean cp_clean c_clean fr_clean ja_clean js_clean py_clean rs_clean docs_clean $(MFLAGS) -j --no-print-directory

.PHONY: cs_%
cs_%: LICENSE
	@$(MAKE) -C csharp $* $(MFLAGS) --no-print-directory

.PHONY: cp_%
cp_%: LICENSE
	@$(MAKE) -C cplusplus $* $(MFLAGS) --no-print-directory

.PHONY: c_%
c_%: LICENSE
	@$(MAKE) -C c $* $(MFLAGS) --no-print-directory

.PHONY: docs_%
docs_%: LICENSE
	@$(MAKE) -C docs $* $(MFLAGS) --no-print-directory

.PHONY: fr_%
fr_%: LICENSE
	@$(MAKE) -C fortran $* $(MFLAGS) --no-print-directory

.PHONY: ja_%
ja_%: LICENSE
	@$(MAKE) -C java $* $(MFLAGS) --no-print-directory

.PHONY: js_%
js_%: LICENSE
	@$(MAKE) -C javascript $* $(MFLAGS) --no-print-directory

.PHONY: lu_%
lu_%: LICENSE
	@$(MAKE) -C lua $* $(MFLAGS) --no-print-directory

.PHONY: py_%
py_%: LICENSE
	@$(MAKE) -C python $* $(MFLAGS) --no-print-directory

.PHONY: rs_%
rs_%: LICENSE
	@$(MAKE) -C rust $* $(MFLAGS) --no-print-directory

%:
	@$(MAKE) c_$* cp_$* cs_$* fr_$* ja_$* js_$* lu_$* py_$* rs_$* $(MFLAGS) --no-print-directory

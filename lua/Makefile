BLUE=\033[0;34m
NC=\033[0m  # No Color
COV?=false

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	Run through all Lua tests in sequence."
	@echo "  $(BLUE)test_auto$(NC)	Run through all Lua tests (parallel execution not implemented)."
	@echo "  $(BLUE)clean$(NC)  	Clean up any stray files."

.PHONY: test
test: ../LICENSE
ifneq ($(COV),false)
	@lua -lluacov test.lua && luacov
else
	@lua test.lua
endif

test_%:
	@$(MAKE) test $(MFLAGS)

.PHONY: clean
clean:
	@echo

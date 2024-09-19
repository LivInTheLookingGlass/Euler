BLUE=\033[0;34m
NC=\033[0m  # No Color
CFORTRAN?=flang-new

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	Run through all Lua tests in sequence."
	@echo "  $(BLUE)test_auto$(NC)	Run through all Lua tests (parallel execution not implemented)."
	@echo "  $(BLUE)clean$(NC)  	Clean up any stray files."

.PHONY: test
test: ../LICENSE
	@$(CFORTRAN) -c src/*.f90
	@$(CFORTRAN) *.o test.f90
	@./a.out

test_%:
	@$(MAKE) test $(MFLAGS)

.PHONY: clean
clean:
	@rm *.o *.mod a.out

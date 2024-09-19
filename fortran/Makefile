BLUE=\033[0;34m
NC=\033[0m  # No Color
FC?=flang-new

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	Run through all Fortran tests in sequence."
	@echo "  $(BLUE)test_auto$(NC)	Run through all Fortran tests (parallel execution not implemented)."
	@echo "  $(BLUE)clean$(NC)  	Clean up any stray files."

.PHONY: test
test: ../LICENSE
	@$(FC) -c src/*.f90
	@$(FC) *.o test.f90
	@./a.out

test_%:
	@$(MAKE) test $(MFLAGS)

.PHONY: clean
clean:
	@rm *.o *.mod a.out

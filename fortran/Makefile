BLUE=\033[0;34m
NC=\033[0m  # No Color
FC?=flang-new
COV?=false

ifeq ($(FC),ifort)
opt_args= -Wall -Werror -O2 -march=native -qwholeprogram
else ifeq ($(FC),nvfortran)
opt_args= -Wall -Werror -O2 -march=native
else
opt_args= -Wall -Werror -O1 -flto
endif

ifneq ($(COV),false)
cov_args= --coverage
else
cov_args=
endif

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	Run through all Fortran tests in sequence."
	@echo "  $(BLUE)test_auto$(NC)	Run through all Fortran tests (parallel execution not implemented)."
	@echo "  $(BLUE)clean$(NC)  	Clean up any stray files."

.PHONY: test
test: ../LICENSE
	@$(FC) $(opt_args) $(cov_args) -c src/*.f90
	@$(FC) $(opt_args) $(cov_args) *.o test.f90 -o test_runner
	@./test_runner

test_%:
	@$(MAKE) test $(MFLAGS)

.PHONY: clean
clean:
	@rm *.o *.mod test_runner

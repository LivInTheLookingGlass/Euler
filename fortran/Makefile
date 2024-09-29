BLUE=\033[0;34m
NC=\033[0m  # No Color
FC?=flang-new
COV?=false
BUILD_DIR=build
SRC_DIR=src
INCLUDE_DIR=$(SRC_DIR)/include
SRC_FILES=$(wildcard $(SRC_DIR)/*.f90) $(wildcard $(SRC_DIR)/include/*.f90)
INCLUDE_FILES=$(wildcard $(INCLUDE_DIR)/*.f90)
INCLUDE_OBJS=$(patsubst $(INCLUDE_DIR)/%.f90, $(BUILD_DIR)/include/%.o, $(INCLUDE_FILES))
OBJ_FILES=$(patsubst $(SRC_DIR)/%.f90, $(BUILD_DIR)/%.o, $(SRC_FILES)) $(INCLUDE_OBJS)

GCC_VERSION := $(shell gcc --version | grep ^gcc | sed 's/^.* //g')
GCC_MAJOR := $(shell echo $(GCC_VERSION) | cut -d. -f1)

ifeq ($(FC),ifort)
    opt_args = -Wall -Werror -march=native -qwholeprogram -J$(BUILD_DIR)
else ifeq ($(FC),lfortran)
    opt_args = -J$(BUILD_DIR)
else ifeq ($(FC),nvfortran)
    opt_args = -Wall -Werror -march=native -module $(BUILD_DIR)
else ifneq (,$(findstring flang,$(FC)))
    opt_args = -Werror -march=native -flto -J$(BUILD_DIR)
else ifeq ($(FC),gfortran)
    opt_args = -Wall -Werror -march=native -flto -J$(BUILD_DIR)
    ifneq ($(findstring $(GCC_MAJOR),8 9 10 11),)
        opt_args += -Wno-error=maybe-uninitialized
    endif
else
    opt_args = -Wall -Werror -march=native -flto -J$(BUILD_DIR)
endif

cov_args=
ifneq ($(COV),false)
    cov_args= -fprofile-arcs -ftest-coverage -O0
else ifneq ($(FC),lfortran)
    cov_args= -O2
endif

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	Run through all Fortran tests in sequence."
	@echo "  $(BLUE)test_auto$(NC)	Run through all Fortran tests (parallel execution not implemented)."
	@echo "  $(BLUE)clean$(NC)  	Clean up any stray files."

$(BUILD_DIR)/include/constants.o: $(INCLUDE_DIR)/constants.f90
	@mkdir -p $(BUILD_DIR)/include
	@$(FC) $(opt_args) $(cov_args) -c $(INCLUDE_DIR)/constants.f90 -o $@

$(BUILD_DIR)/include/%.o: $(INCLUDE_DIR)/%.f90 $(BUILD_DIR)/include/constants.o
	@$(FC) $(opt_args) $(cov_args) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.f90 $(INCLUDE_OBJS)
	@$(FC) $(opt_args) $(cov_args) -c $< -o $@

test_runner: ../LICENSE
	@$(MAKE) $(OBJ_FILES) $(INCLUDE_OBJS) $(MFLAGS) -j --no-print-directory
	@$(FC) $(opt_args) $(cov_args) $(BUILD_DIR)/*.o $(BUILD_DIR)/include/*.o test.f90 -o test_runner

.PHONY: test
test: test_runner
	@./test_runner

test_%:
	@$(MAKE) test $(MFLAGS)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) test_runner

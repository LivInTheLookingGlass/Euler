BLUE=\033[0;34m
NC=\033[0m  # No Color
FC?=flang-new
COV?=false
BUILD_DIR=build
SRC_DIR=src
SRC_FILES=$(wildcard $(SRC_DIR)/*.f90) $(wildcard $(SRC_DIR)/include/*.f90)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.f90, $(BUILD_DIR)/%.o, $(SRC_FILES))
GCC_VERSION := $(shell $(CC) --version | grep -oP 'gcc \K[0-9.]+')
GCC_MAJOR := $(shell echo $(GCC_VERSION) | cut -d. -f1)

$(info Detected GCC Version: $(GCC_VERSION))
$(info Major Version: $(GCC_MAJOR))

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

ifneq ($(COV),false)
    cov_args= -fprofile-arcs -ftest-coverage -O0
else ifeq ($(FC),lfortran)
    cov_args=
else
    cov_args= -O2
endif

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	Run through all Fortran tests in sequence."
	@echo "  $(BLUE)test_auto$(NC)	Run through all Fortran tests (parallel execution not implemented)."
	@echo "  $(BLUE)clean$(NC)  	Clean up any stray files."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.f90
	@mkdir -p $(BUILD_DIR)/include
	$(FC) $(opt_args) $(cov_args) -c $< -o $@

.PHONY: test
test: ../LICENSE
	@$(MAKE) $(OBJ_FILES) $(MFLAGS) -j --no-print-directory
	$(FC) $(opt_args) $(cov_args) $(BUILD_DIR)/*.o $(BUILD_DIR)/include/*.o test.f90 -o test_runner
	@./test_runner

test_%:
	@$(MAKE) test $(MFLAGS)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) test_runner

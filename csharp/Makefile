NOT_TERMUX?=$(shell command -v termux-setup-storage > /dev/null 2>&1 ; echo $$?)
BLUE=\033[0;34m
NC=\033[0m # No Color
COV?=false
ifeq ($(COV),true)
cov_args= --collect:"XPlat Code Coverage" -- DataCollectionRunSettings.DataCollectors.DataCollector.Configuration.IncludeTestAssembly=true
else
cov_args=
endif

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)    	run through all tests in sequence. Utilizes the Xunit framework"
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the Xunit framework"
	@echo "  $(BLUE)dependencies$(NC)	runs dotnet restore"
	@echo "  $(BLUE)lint$(NC)  	runs dotnet format --verify-no-changes"
	@echo "  $(BLUE)clean$(NC) 	clean up any stray files"

.PHONY: clean
clean:
	@dotnet clean || rm -rf ./*/{bin,obj,TestResults} || echo

.PHONY: test
test: ../LICENSE
ifneq ($(NOT_TERMUX),0)
	@dotnet test --nologo -l "console;verbosity=normal" $(cov_args)
endif

.PHONY: test_%
test_%:
	@$(MAKE) test $(MFLAGS) --no-print-directory

.PHONY: dependencies
dependencies:
ifneq ($(NOT_TERMUX),0)
	@dotnet restore
endif

.PHONY: lint
lint:
ifneq ($(NOT_TERMUX),0)
	@dotnet format --verify-no-changes
endif

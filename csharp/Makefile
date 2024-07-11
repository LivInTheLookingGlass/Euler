BLUE=\033[0;34m
NC=\033[0m # No Color

help:
	@echo "  $(BLUE)test$(NC)    	run through all tests in sequence. Utilizes the Xunit framework"
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it. Utilizes the Xunit framework"
	@echo "  $(BLUE)dependencies$(NC)	runs dotnet restore"
	@echo "  $(BLUE)lint$(NC)  	runs dotnet format --verify-no-changes"
	@echo "  $(BLUE)clean$(NC) 	clean up any stray files"

clean:
	dotnet clean || rm ./*/{bin,obj,TestResults} || echo

test: dependencies
	dotnet test --nologo 

test_%: dependencies
	$(MAKE) test

dependencies:
	dotnet restore

lint:
	dotnet format --verify-no-changes

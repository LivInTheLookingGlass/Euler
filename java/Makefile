MVN?=mvn
BLUE=\033[0;34m
NC=\033[0m # No Color

help:
	@echo "  $(BLUE)test$(NC)   	run through all tests in sequence"
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it"
	@echo "  $(BLUE)dependencies$(NC)	grabs all dependencies through maven"
	@echo "  $(BLUE)clean$(NC)  	clean up any stray files"
	@echo "  $(BLUE)lint$(NC)		Run the maven formatter"

clean:
	$(MVN) clean || echo

dependencies:
	$(MVN) install -B

test: dependencies
	$(MVN) -e test -Dtest.single

test_auto: dependencies
	$(MVN) -e test -T 1C

test_%: dependencies
	$(MVN) -e test -T $*

lint:
	$(MVN) formatter:format

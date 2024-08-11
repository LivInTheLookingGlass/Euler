MVN?=mvn
MVN_FLAGS?= -e
BLUE=\033[0;34m
NC=\033[0m # No Color

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	run through all tests in sequence"
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it"
	@echo "  $(BLUE)clean$(NC)  	clean up any stray files"
	@echo "  $(BLUE)lint$(NC)		Run the maven formatter"

.PHONY: clean
clean:
	@$(MVN) clean || echo

.PHONY: test
test: ../LICENSE
	@$(MVN) $(MVN_FLAGS) test -Dtest.single

test_auto: ../LICENSE
	@$(MVN) $(MVN_FLAGS) test -T 1C

.PHONY: test_%
test_%: ../LICENSE
	@$(MVN) $(MVN_FLAGS) test -T $*

.PHONY: lint
lint:
	@$(MVN) $(MVN_FLAGS) formatter:format

BLUE=\033[0;34m
NC=\033[0m # No Color

help:
	@echo "  $(BLUE)test$(NC)   	run through all tests in sequence."
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it"
	@echo "  $(BLUE)clean$(NC)  	clean up any stray files"

test:
	cargo test -j 1

test_auto:
	cargo test

test_%:
	cargo test -j $*

clean:
	cargo clean || echo

BLUE=\033[0;34m
NC=\033[0m # No Color
RUSTFLAGS?="-Copt-level=2"

.PHONY: help
help:
	@echo "  $(BLUE)test$(NC)   	run through all tests in sequence."
	@echo "  $(BLUE)test_*$(NC) 	run through all tests in parallel with the given number of threads. Use auto to allow the test runner to determine it"
	@echo "  $(BLUE)clean$(NC)  	clean up any stray files"

.PHONY: test
test: ../LICENSE
	cargo test -j 1

test_auto: ../LICENSE
	cargo test

.PHONY: test_%
test_%: ../LICENSE
	cargo test -j $*

.PHONY: clean
clean:
	cargo clean || echo

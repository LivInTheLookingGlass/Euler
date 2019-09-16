
PY?=python3

test_%: dependencies
	$(PY) -m pytest -v -n$* test_euler.py

test: dependencies
	$(PY) -m pytest -v --benchmark-sort=fullname test_euler.py

dependencies:
	cd ../python && $(MAKE) dependencies

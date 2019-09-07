test_%: dependencies
	python3 -m pytest -v --benchmark-sort=fullname test_euler.py

test: dependencies
	python3 -m pytest -v --benchmark-sort=fullname test_euler.py

dependencies:
	cd ../python && $(MAKE) dependencies

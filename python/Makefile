pytest_args?=

test: dependencies _test

test_2:
	$(MAKE) test pytest_args=-n2

test_3:
	$(MAKE) test pytest_args="-n3"

test_4:
	$(MAKE) test pytest_args="-n4"

test_5:
	$(MAKE) test pytest_args="-n5"

test_6:
	$(MAKE) test pytest_args="-n6"

test_7:
	$(MAKE) test pytest_args="-n7"

test_8:
	$(MAKE) test pytest_args="-n8"


_test:
	python3 -m pytest -v --benchmark-sort=fullname $(pytest_args)

dependencies:
	python3 -m pip install -r requirements.txt --user

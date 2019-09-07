pytest_args?= --mypy --mypy-ignore-missing-imports --flake8 --isort

test: dependencies _test

test_%:
	$(MAKE) test pytest_args="-n$*"

_test:
	python3 -m pytest -v --benchmark-sort=fullname $(pytest_args)

dependencies:
	python3 -m pip install -r requirements.txt --user

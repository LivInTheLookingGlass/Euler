test: dependencies
	dotnet test

test_%: dependencies
	echo "WARNING: multithreaded tests not supported on javascript"
	$(MAKE) test

dependencies:
	dotnet restore


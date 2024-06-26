test: dependencies
	dotnet test --nologo 

test_%: dependencies
	$(MAKE) test

dependencies:
	dotnet restore

lint:
	dotnet format --verify-no-changes
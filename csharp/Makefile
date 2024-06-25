test: dependencies
	dotnet test --nologo 

test_%: dependencies
	$(MAKE) test

dependencies:
	dotnet restore


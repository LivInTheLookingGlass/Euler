IF DEFINED PIP (
    %PYPY%
    cd python
    %PIP% install -r requirements.txt
    IF DEFINED LINT (
        %RUN% -m pytest -v --mypy --mypy-ignore-missing-imports --flake8 --isort -k "not test_problem and not test_is_prime and not test_groupwise" || goto :error
    ) ELSE (
        %RUN% -m pytest test_euler.py -v --benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-verbose || goto :error
    )
) ELSE (
    IF DEFINED NODE (
        powershell -Command "Install-Product node $env:NODE"
        cd javascript
        IF DEFINED LINT (
            npm install eslint-config-google@latest eslint@>=5.16.0
            npx eslint *.js || goto :error
        ) ELSE (
            npm install
            npx mocha || goto :error
        )
    ) ELSE (
        cd c
        C:\Python36\python -m pip install -r requirements.txt
        %WIN_SDK%
        %VCVARS%
        C:\Python36\python -m pytest test_euler.py -v --benchmark-min-time=0.05 --benchmark-group-by=fullfunc --benchmark-sort=fullname --benchmark-verbose || goto :error
    )
)
goto :EOF

:error
ECHO Failed with error #%errorlevel%.
exit /b %errorlevel%

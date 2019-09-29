IF DEFINED PIP (
    ECHO %PYTHON% %PYTHON_VERSION%%APPVEYOR_BUILD_FOLDER%
    ECHO "3"
    set HOME=%APPVEYOR_BUILD_FOLDER%
    ECHO "4"
    %PYPY%
    dir -r
    dir /S
    ECHO "5"
    cd python
    ECHO "6"
    %PIP% install -r requirements.txt
    IF DEFINED LINT (
        ECHO "7"
        %RUN% -m pytest -v --mypy --mypy-ignore-missing-imports --flake8 --isort -k "not test_problem and not test_is_prime and not test_groupwise" || goto :error
    ) ELSE (
        ECHO "7"
        %RUN% -m pytest test_euler.py -v --benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-verbose || goto :error
    )
) ELSE (
    IF DEFINED NODE (
        dir C:\avvm\node
        ECHO "3"
        powershell -Command "Install-Product node $env:NODE"
        ECHO "4"
        cd javascript
        ECHO "5"
        IF DEFINED LINT (
            npm install eslint-config-google@latest eslint@>=5.16.0
            ECHO "6"
            npx eslint *.js || goto :error
        ) ELSE (
            npm install
            ECHO "6"
            npx mocha || goto :error
        )
    ) ELSE (
        cd c
        C:\Python36\python -m pip install -r requirements.txt
        %WIN_SDK%
        ECHO %VCVARS%
        %VCVARS%
        C:\Python36\python -m pytest test_euler.py -v --benchmark-min-time=0.05 --benchmark-sort=fullname --benchmark-verbose || goto :error
    )
)
goto :EOF

:error
ECHO Failed with error #%errorlevel%.
exit /b %errorlevel%

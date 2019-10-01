
set -e;
if [ $pyver ]; then
    if [ $pyver != pypy3 ]; then
        git clone https://github.com/gappleto97/terryfy;
        source terryfy/travis_tools.sh;
        get_python_environment  $pydist $pyver;
    fi
    if [ $pyver == pypy3 ]; then
        brew install $pyver;
        export PYTHON_EXE=$pyver;
        export PIP_CMD="$PYTHON_EXE -m pip";
    fi
    $PIP_CMD install virtualenv;
    $PYTHON_EXE -m virtualenv -p $PYTHON_EXE venv;
    source venv/bin/activate;
    if [ $linter ]; then
        make pytest PY=python LINT=true USER_FLAG=
    else
        make pytest PY=python LINT=false MYPY= USER_FLAG=
    fi
elif [ $jsver ]; then
    if [ $linter ]; then
        cd javascript;
        npm install eslint-config-google@latest eslint@>=5.16.0;
        npx eslint *.js && echo "Linting successful!"
    else
        make jstest;
    fi
else
    if [ $linter ]; then
        brew install llvm;
        ln -s "/usr/local/opt/llvm/bin/clang-tidy" "/usr/local/bin/clang-tidy";
        make clint;
    else
        if [ $pcc ]; then
            brew install flex bison
            mkdir pcc pcc-libs
            wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/pcc-1.1.0.tgz | tar -xz -C pcc --strip-components=1
            wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/pcc-libs-1.1.0.tgz | tar -xz -C pcc-libs --strip-components=1
            cd pcc
            ./configure
            sudo make && sudo make install
            cd ../pcc-libs
            ./configure
            sudo make && sudo make install
            cd ..
        elif [ $GCC_OVERRIDE ]; then
            brew install gcc;
        fi
        make ctest;
    fi
fi

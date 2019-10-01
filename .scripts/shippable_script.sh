set -e;
if [ $pyver ]; then
    if [ $linter ]; then
        make pytest LINT=true PY=python USER_FLAG=
    else
        export PY_EXE=python
        if [ $py36 ]; then
            sudo add-apt-repository -y ppa:jonathonf/python-3.6
            sudo apt-get update --fix-missing
            sudo apt-get install python3.6
            virtualenv -p python3.6 venv
            export PY_EXE=$PWD/venv/bin/python
        fi
        make pytest LINT=false PY=$PY_EXE USER_FLAG= MYPY=
    fi
elif [ $jsver ]; then
    if [ $linter ]; then
        make jsdependencies
        cd javascript;
        npm install eslint-config-google@latest eslint@>=5.16.0;
        npx eslint *.js && echo "Linting successful!"
    else
        make jstest
    fi
else
    if [ $linter ]; then
        sudo apt-get update
        sudo apt-get install -y clang-tidy
        cd c
        clang-tidy --help
        clang-tidy *.c
    else
        sudo apt-get update
        if [ $pcc ]; then
            sudo apt-get install -y build-essential flex bison
            mkdir pcc pcc-libs
            wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/pcc-1.1.0.tgz | tar -xz --no-seek -C pcc --strip-components=1
            wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/pcc-libs-1.1.0.tgz | tar -xz --no-seek -C pcc-libs --strip-components=1
            cd pcc
            sed -i 's/MANPAGE=@BINPREFIX@cpp/MANPAGE=@BINPREFIX@pcc-cpp/' cc/cpp/Makefile.in
            ./configure --prefix=/usr --libexecdir=/usr/lib/{x86_64,i386}-linux-gnu
            sudo make && sudo make install
            cd ../pcc-libs
            ./configure --prefix=/usr --libexecdir=/usr/lib/{x86_64,i386}-linux-gnu
            sudo make && sudo make install
            cd ..
        else
            sudo apt-get install -y $COMPILER_OVERRIDE python3-pip
        fi
        cd c && make test USER_FLAG=
    fi
fi

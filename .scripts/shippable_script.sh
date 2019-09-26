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
        make clint
    else
        sudo apt-get update
        sudo apt-get install -y gcc clang tcc python3-pip
        if [ $pcc ]; then
            sudo apt-get install -y build-essential flex bison
            mkdir pcc pcc-libs
            wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc/pcc-20190926.tgz | tar -xz --no-seek -C pcc --strip-components=1
            wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc-libs/pcc-libs-20190926.tgz | tar -xz --no-seek -C pcc-libs --strip-components=1
            cd pcc
            sed -i 's/MANPAGE=@BINPREFIX@cpp/MANPAGE=@BINPREFIX@pcc-cpp/' cc/cpp/Makefile.in
            ./configure --prefix=/usr --libexecdir=/usr/lib/{x86_64,i386}-linux-gnu
            sudo make install
            cd ../pcc-libs
            ./configure --prefix=/usr --libexecdir=/usr/lib/{x86_64,i386}-linux-gnu
            sudo make install
            cd ..
        fi
        cd c && make test USER_FLAG=
    fi
fi

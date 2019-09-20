
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
    virtualenv -p $PYTHON_EXE venv;
    source venv/bin/activate;
    if [ $linter ]; then
        make pytest PY=python LINT=true USER=
    else
        make pytest PY=python LINT=false USER=
    fi
else
    make jstest
fi
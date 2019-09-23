python -c "import urllib; urllib.urlretrieve('https://bitbucket.org/pypy/pypy/downloads/pypy3.6-v7.1.1-win32.zip', 'pypy3.6-v7.1.1-win32.zip'); urllib.urlretrieve('https://bootstrap.pypa.io/get-pip.py', 'get-pip.py')"
7z x pypy3.6-v7.1.1-win32.zip > Out-Null
pypy3.6-v7.1.1-win32\pypy get-pip.py
pypy3.6-v7.1.1-win32\pypy -m pip install setuptools
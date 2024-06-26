PY?=python3
USER_FLAG?=--user
PIP?=$(PY) -m pip

ifneq ($(https_proxy), )
PROXY_ARG=--proxy=$(https_proxy)
else
ifneq ($(http_proxy), )
PROXY_ARG=--proxy=$(http_proxy)
else
PROXY_ARG=
endif
endif

test_%: dependencies
	$(PY) -m pytest -vl -n$* test_euler.py

test: dependencies
	$(PY) -m pytest -vl --benchmark-sort=fullname --benchmark-group-by=fullfunc --benchmark-verbose test_euler.py

dependencies:
	git submodule init
	git submodule update
	$(PIP) install -r requirements.txt $(USER_FLAG) $(PROXY_ARG)

lint:
	if test -z "$(clang-tidy p0000_template.c -warnings-as-errors=* 2>&1 | grep "Unknown command line argument")"; then \
		clang-tidy *.c -warnings-as-errors=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling; \
	else \
		clang-tidy *.c; \
	fi

ifeq ($(OS),Windows_NT)
else
pcc:
	sudo apt-get install -y build-essential flex bison
	mkdir pcc pcc-libs
	wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/pcc-1.1.0.tgz | tar -xz --no-seek -C pcc --strip-components=1
	wget -O - -o /dev/null http://pcc.ludd.ltu.se/ftp/pub/pcc-releases/pcc-libs-1.1.0.tgz | tar -xz --no-seek -C pcc-libs --strip-components=1
	cd pcc; \
	sed -i 's/MANPAGE=@BINPREFIX@cpp/MANPAGE=@BINPREFIX@pcc-cpp/' cc/cpp/Makefile.in; \
	./configure --prefix=/usr --libexecdir=/usr/lib/{x86_64,i386}-linux-gnu; \
	sudo make && sudo make install; \
	cd ../pcc-libs; \
	./configure --prefix=/usr --libexecdir=/usr/lib/{x86_64,i386}-linux-gnu; \
	sudo make && sudo make install

icc:
	mkdir iccdir
	wget -O - -o /dev/null https://registrationcenter-download.intel.com/akdlm/irc_nas/15873/intel-sw-tools-installer.tar.gz | tar -xz --no-seek -C iccdir  --strip-components=1
	sudo apt-get update
	sudo apt-get install -y cpio
	cd iccdir; \
	sed -i -e "s/ACCEPT_EULA=decline/ACCEPT_EULA=accept/g" silent.cfg; \
	sed -i -e "s/ACTIVATION_TYPE=no_license/ACTIVATION_TYPE=serial_number/g" silent.cfg; \
	echo "ACTIVATION_SERIAL_NUMBER=CKDX-WNDG7BK7" >> silent.cfg; \
	echo "SELECTION_CONFIG_FILES_PATH=$PWD/packages.json" >> silent.cfg; \
	echo '{"selections":[{"moduleId":"intel_cpp_compiler"},{"moduleId":"intel_threading_building_blocks","isDependencyTool":true}]}' > packages.json; \
	sudo ./install.sh -s silent.cfg; \
	PATH="/opt/intel/system_studio_2019/bin${PATH:+:${PATH}}"; export PATH
endif

native:
	$(CC) *.c Unity/src/unity.c $(CFLAGS)

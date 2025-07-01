# libmpd++

libmpd++ is a C++ library for parsing and manipulating DASH MPDs.

This library is licensed using the LGPLv3 license.

The library makes use of the [libxml++](https://libxmlplusplus.sourceforge.net/) library for parsing and formatting of XML. libmpd++ requires a version of libxml++ of 3.x, 4.x or 5.x. If one of these versions is not already installed on your build system then libmpd++ will attempt to download and build libxml++-5.4.0. If this happens then you will need to have the libxml2 library development files and the mm-common package installed on your system for the library to compile.

The library also relies on C++-20 features that were only introduced in GCC version 14 and above. To use the GCC 14 compiler on Ubuntu 24.04 you will need to do the following commands:

```sh
sudo apt -y install software-properties-common
sudo add-apt-repository universe
sudo apt -y install gcc-14 g++-14
sudo sh -c 'for i in cpp g++ gcc gcc-ar gcc-nm gcc-ranlib gcov gcov-dump gcov-tool lto-dump; do rm -f /usr/bin/$i; ln -s $i-14 /usr/bin/$i; done'
```

The commands above do the following actions:

1. Install the `add-apt-repository` command.
1. Add the universe repository, which holds the GCC version 14 packages.
1. Install GCC version 14 C and C++ compilers.
1. Replace the default links for the GCC commands. This replaces the Ubuntu 24.04 default GCC version (13) with GCC version 14 for the default GCC commands.

Please see the [documentation on GitHub pages](https://bbc.github.io/libmpdpp/) for more information.

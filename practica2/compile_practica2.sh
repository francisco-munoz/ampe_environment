#!/bin/bash

if test $# -ne 1
then
    echo "Usage: $0 [install|clean]"
fi

if test "$1" == "install"
then
    echo "The system is ready to be installed"
    if ! grep -q avx2 /proc/cpuinfo
    then
        echo "AVX2 is not supported in this CPU."
        exit 1
    fi

    echo "AVX2 support: Yes"

    echo "Compiling PRACTICA2 User interface"
    g++ -mavx src/main.cpp src/practica2.cpp -o practica2_interface
    if test $? -eq 1
    then
        echo "Please fix the code!"
	exit 1
    fi
    CFLAGS="-mavx" python setup.py install
    exit 0

elif test "$1" == "clean"
then
   rm -rf build/ dist/ torch_practica2.egg-info/ practica2_interface 
fi



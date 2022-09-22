#!/bin/bash
# The vemu build script

# may be Unix platform
EXE_SUFFIX=""
PLATFORM=`uname -s`
MACHINE="???"
case $PLATFORM in
	Linux)
		EXE_SUFFIX=
		MACHINE=Linux
		;;
	FreeBSD|NetBSD|OpenBSD)
		EXE_SUFFIX=
		MACHINE=$PLATFORM
		;;
	Darwin*)
		EXE_SUFFIX=.app
		MACHINE=Darwin
		;;
	CYGWIN*)
		EXE_SUFFIX=.exe
		MACHINE="Windows/Cygwin"
		;;
	MINGW*)
		EXE_SUFFIX=.exe
		MACHINE="Windows/MinGW"
		;;
	MSYS*)
		EXE_SUFFIX=.exe
		MACHINE="Windows/Msys2"
		;;
	*)
		printf "unknown platform: %s\n" $PLATFORM
		exit 1
		;;
esac
printf "Host platform is: \"%s\" (aka %s)" $MACHINE $PLATFORM
mkdir -p bin
cd src
shopt -s globstar
gcc -I. -o ../bin/vemu${EXE_SUFFIX} vemu/**/**/**/**/**.c
shopt -u globstar

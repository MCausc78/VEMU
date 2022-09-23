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
		PLATFORM=linux
		;;
	FreeBSD|NetBSD|OpenBSD)
		EXE_SUFFIX=
		MACHINE=$PLATFORM
		case $PLATFORM in
			FreeBSD) PLATFORM=freebsd;;
			NetBSD) PLATFORM=netbsd;;
			OpenBSD) PLATFORM=openbsd;;
		esac
		;;
	Darwin*)
		EXE_SUFFIX=.app
		MACHINE=Darwin
		PLATFORM=darwin
		;;
	CYGWIN*)
		EXE_SUFFIX=.exe
		MACHINE="Windows/Cygwin"
		PLATFORM=cygwin
		;;
	MINGW*)
		EXE_SUFFIX=.exe
		MACHINE="Windows/MinGW"
		PLATFORM=cygwin
		;;
	MSYS*)
		EXE_SUFFIX=.exe
		MACHINE="Windows/Msys2"
		PLATFORM=msys
		;;
	*)
		printf "unknown platform: %s\n" $PLATFORM
		exit 1
		;;
esac
printf "Host platform is: \"%s\" (aka %s)\n" $MACHINE $PLATFORM
mkdir -p bin
cd src
shopt -s globstar
gcc -DVEMU_MODE=0 -I. -o ../bin/vemu-${PLATFORM}${EXE_SUFFIX} vemu/**/**/**/**/**.c
gcc -DVEMU_MODE=1 -I. -o ../bin/vemu-dis-${PLATFORM}${EXE_SUFFIX} vemu/**/**/**/**/**.c
shopt -u globstar

#!/bin/bash

VALGRIND=""
if [ "$1" == "debug" ]; then
	export VALGRIND=valgrind
	export DEBUG=1
fi
${VALGRIND}  ./SingleDownload -n -r -f

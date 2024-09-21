#!/bin/bash

#DIR="./lib"
COMMAND="cmake --install buildtree"

cmake -B buildtree
cmake --build buildtree

#if [ ! -d "$DIR" ]; then
#	$COMMAND
#fi

cmake --install buildtree


#./bin/run

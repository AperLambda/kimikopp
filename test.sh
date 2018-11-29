#!/bin/sh

# Some color variables.
RED='\033[0;91m'
NC='\033[0m'

if [ ! -d "build" ]; then
sh ./build.sh
fi

if [ ! -d "build" ]; then
echo "${RED}Cannot test kimiko: Cannot build the library.${NC}"
return 1;
fi

cd build/
./tests/kimiko_test
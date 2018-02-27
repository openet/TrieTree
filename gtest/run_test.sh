#!/bin/bash

GTEST_PATH=`cat ../make.make | grep GTEST_PATH | sed 's/.*:=[ \t]*\(.*\)/\1/g'`
GTEST_PATH="${GTEST_PATH}/lib"

LD_LIBRARY_PATH=${GTEST_PATH}:../release
./gtest 

#!/bin/bash

################################################################################

cd bin
./tests --gtest_break_on_failure

read -p "Press any key to continue... " -n1 -s

################################################################################

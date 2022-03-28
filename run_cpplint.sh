#!/bin/bash

################################################################################

rm -f out_cpplint.txt

cpplint \
    --filter=-build/c++11,+build/c++14,-readability/multiline_comment,-readability/alt_tokens,-whitespace/parens,-whitespace/braces,-whitespace/indent,-whitespace/comments,-whitespace/newline,-whitespace/blank_line,-whitespace/comma \
    --linelength=100 \
    --extensions=h,cpp --root=./ \
    ./mcutil/*.h \
    ./mcutil/*/*.h \
    ./mcutil/*/*.cpp \
    2> out_cpplint.txt

################################################################################

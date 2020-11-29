#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
cppcheck project --enable=all --error-exitcode=1 -I project/include --suppress=missingIncludeSystem

print_header "RUN cpplint.py for sources"
cpplint --extensions=c project/include/*.h project/src/*.c

print_header "RUN cpplint.py for unit_tests"
cpplint --extensions=cpp project/unit_tests/*.cpp

print_header "RUN cpplint.py for stress_tests"
cpplint --extensions=cpp project/stress_tests/*.cpp

print_header "SUCCESS"

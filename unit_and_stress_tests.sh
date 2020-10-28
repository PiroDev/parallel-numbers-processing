#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

mkdir -p out

print_header "RUN unit testing for serial library build with valgrind"
valgrind --leak-check=full ./build/unit_tests_serial
gcovr build/CMakeFiles/serial.dir/project/lib/serial -o out/serial_coverage_report.txt
echo
cat out/serial_coverage_report.txt
echo

print_header "RUN unit testing for multithread library build with valgrind"
valgrind --leak-check=full ./build/unit_tests_parallel
gcovr build/CMakeFiles/parallel.dir/project/lib/parallel -o out/parallel_coverage_report.txt
echo
cat out/parallel_coverage_report.txt
echo

print_header "RUN stress testing for multithred and serial libraries (result compare)"
cd build
export LD_LIBRARY_PATH=`pwd`
./stress_tests

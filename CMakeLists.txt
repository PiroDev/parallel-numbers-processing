cmake_minimum_required(VERSION 3.1)

project(IZ2 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -Wpedantic --coverage")
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wpedantic")

if(DEFINED MODE)
    if(${MODE} STREQUAL DEBUG)
        set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-g3 -ggdb")
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g3 -ggdb")
    endif()
endif()

set(project_dir project)
set(lib_dir lib)
set(inc_dir include)
set(src_dir src)
set(unit_dir unit_tests)
set(stress_dir stress_tests)

set(RUNTIME_OUTPUT_DIRECTORY ${IZ2_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${IZ2_SOURCE_DIR}/shared)
set(ARCHIVE_OUTPUT_DIRECTORY ${IZ2_SOURCE_DIR}/static)

# app binary
set(app_sources)
aux_source_directory(${IZ2_SOURCE_DIR}/${project_dir}/${src_dir} app_sources)
add_executable(app ${app_sources})
target_include_directories(app PUBLIC ${project_dir}/${inc_dir})

# static serial lib
set(serial_sources)
aux_source_directory(${IZ2_SOURCE_DIR}/${project_dir}/${lib_dir}/serial serial_sources)
add_library(serial STATIC ${serial_sources})
target_include_directories(serial PUBLIC ${IZ2_SOURCE_DIR}/${project_dir}/${inc_dir})

# shared parallel lib
set(parallel_sources)
aux_source_directory(${IZ2_SOURCE_DIR}/${project_dir}/${lib_dir}/parallel parallel_sources)
add_library(parallel SHARED ${parallel_sources})
target_include_directories(parallel PUBLIC ${IZ2_SOURCE_DIR}/${project_dir}/${inc_dir})
target_link_libraries(parallel pthread)

# unit_tests_serial binary
set(unit_tests_serial_sources)
aux_source_directory(${IZ2_SOURCE_DIR}/${project_dir}/${unit_dir} unit_tests_serial_sources)
add_executable(unit_tests_serial ${unit_tests_serial_sources})
target_include_directories(unit_tests_serial PUBLIC ${project_dir}/${inc_dir})

# unit_tests_parallel binary
set(unit_tests_parallel_sources)
aux_source_directory(${IZ2_SOURCE_DIR}/${project_dir}/${unit_dir} unit_tests_parallel_sources)
add_executable(unit_tests_parallel ${unit_tests_parallel_sources})
target_include_directories(unit_tests_parallel PUBLIC ${project_dir}/${inc_dir})

# stress_tests binary
set(stress_tests_sources)
aux_source_directory(${IZ2_SOURCE_DIR}/${project_dir}/${stress_dir} stress_tests_sources)
add_executable(stress_tests ${stress_tests_sources})
target_include_directories(stress_tests PUBLIC ${project_dir}/${inc_dir})

target_link_libraries(unit_tests_serial serial gtest gcov)
target_link_libraries(unit_tests_parallel parallel gtest gcov)
target_link_libraries(stress_tests serial gtest dl gcov)

option(MULTITHREAD "use multithread lib" OFF)

if(MULTITHREAD)
    target_link_libraries(app parallel)
else()
    target_link_libraries(app serial)
endif()

cmake_minimum_required(VERSION 3.7)
project(CAB301Assignment2)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

set(CMAKE_CXX_STANDARD 14)

enable_cxx_compiler_flag_if_supported("-Wall")

set(SOURCE_FILES main.cpp)
add_executable(Assignment ${SOURCE_FILES})
add_executable(Assignment_Timings ${SOURCE_FILES})
add_executable(Assignment_Logging ${SOURCE_FILES})
add_executable(Assignment_Testing ${SOURCE_FILES})
add_executable(Assignment_Operations ${SOURCE_FILES})

target_compile_definitions(Assignment_Timings PRIVATE TIMING=1)
target_compile_definitions(Assignment_Logging PRIVATE LOGGING=1)
target_compile_definitions(Assignment_Testing PRIVATE TEST=1)
target_compile_definitions(Assignment_Operations PRIVATE OPERATIONS=1)
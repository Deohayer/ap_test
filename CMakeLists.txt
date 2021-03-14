cmake_minimum_required(VERSION 2.9)

project(ap_int_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include everything in dependencies
include_directories(deps/external deps/internal)

#
# Google Test dependency
#

# Path to Google Test directories
set(GTEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/../deps/external/gtest)
set(GTEST_DL_DIR ${GTEST_DIR}/download)
set(GTEST_SRC_DIR ${GTEST_DIR}/src)
set(GTEST_BUILD_DIR ${GTEST_DIR}/build)

# Download and unpack googletest at configure time
configure_file(CMakeLists_gtest.txt ${GTEST_DL_DIR}/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${GTEST_DL_DIR} )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${GTEST_DL_DIR} )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${GTEST_SRC_DIR}
                 ${GTEST_BUILD_DIR}
                 EXCLUDE_FROM_ALL)

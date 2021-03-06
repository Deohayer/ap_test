cmake_minimum_required(VERSION 2.9)

project(ap_int_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

enable_testing()

# Include everything in dependencies
set(DEPS_DIR ${CMAKE_CURRENT_BINARY_DIR}/../deps)
set(DEPS_EX_DIR ${DEPS_DIR}/external)
set(DEPS_IN_DIR ${DEPS_DIR}/internal)

#
# Google Test dependency
#

# Path to Google Test directories
set(GTEST_DIR ${DEPS_EX_DIR}/gtest)
set(GTEST_DL_DIR ${GTEST_DIR}/download)
set(GTEST_SRC_DIR ${GTEST_DIR}/src)
set(GTEST_BUILD_DIR ${GTEST_DIR}/build)

# Download and unpack googletest at configure time
configure_file(CMakeLists_gtest.txt ${GTEST_DL_DIR}/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${GTEST_DL_DIR}
)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${GTEST_DL_DIR}
)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
  ${GTEST_SRC_DIR}
  ${GTEST_BUILD_DIR}
  EXCLUDE_FROM_ALL
)

# Add include path
include_directories(${GTEST_SRC_DIR}/googletest/include)

#
# AP library dependency
#

# Path to AP directories
set(AP_DIR ${DEPS_EX_DIR}/ap)
set(AP_DL_DIR ${AP_DIR}/download)
set(AP_SRC_DIR ${AP_DIR}/ap)

# Download and unpack ap at configure time
configure_file(CMakeLists_ap.txt ${AP_DL_DIR}/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${AP_DL_DIR}
)
if(result)
  message(FATAL_ERROR "CMake step for ap failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${AP_DL_DIR}
)
if(result)
  message(FATAL_ERROR "Build step for ap failed: ${result}")
endif()

# Add include path
include_directories(${AP_DIR})

file(GLOB_RECURSE AP_SRC 
"${AP_DIR}/*.cpp")

#
# time_metric library dependency
#

# Path to time_metric directories
set(TIME_DIR ${DEPS_EX_DIR}/time_metric)
set(TIME_DL_DIR ${TIME_DIR}/download)
set(TIME_SRC_DIR ${TIME_DIR}/time_metric)

# Download and unpack time at configure time
configure_file(CMakeLists_time.txt ${TIME_DL_DIR}/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${TIME_DL_DIR}
)
if(result)
  message(FATAL_ERROR "CMake step for time failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${TIME_DL_DIR}
)
if(result)
  message(FATAL_ERROR "Build step for time failed: ${result}")
endif()

# Add include path
include_directories(${TIME_DIR})

#
# Boost dependency
#

# Path to Boost directory
set(BOOST_DIR ${DEPS_IN_DIR}/boost)

# Add include path
include_directories(${BOOST_DIR})

#
# ap_test
#

# Path to ap_test source directory
set(AP_TEST_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/../src)

# Common files
set(COMMON_SRC_FILES
${AP_TEST_SRC_DIR}/common/digit.cpp
${AP_TEST_SRC_DIR}/common/int_builder.cpp)

# Validation subproject
set(VALIDATION_SRC_DIR ${AP_TEST_SRC_DIR}/validation)
set(VALIDATION_SRC_FILES
${COMMON_SRC_FILES} 
${VALIDATION_SRC_DIR}/validate.cpp
${AP_SRC})

add_executable(ap_validate ${VALIDATION_SRC_FILES})
target_link_libraries(ap_validate gtest_main)

# Measurement subproject
set(MEASUREMENT_SRC_DIR ${AP_TEST_SRC_DIR}/measurement)
set(MEASUREMENT_SRC_FILES
${COMMON_SRC_FILES} 
${MEASUREMENT_SRC_DIR}/measure.cpp
${AP_SRC})

add_executable(ap_measure ${MEASUREMENT_SRC_FILES})
target_link_libraries(ap_measure gtest_main)

# Sandbox subproject
set(SANDBOX_SRC_DIR ${AP_TEST_SRC_DIR}/sandbox)
set(SANDBOX_SRC_FILES
${COMMON_SRC_FILES} 
${SANDBOX_SRC_DIR}/sandbox.cpp
${AP_SRC})

add_executable(ap_sandbox ${SANDBOX_SRC_FILES})

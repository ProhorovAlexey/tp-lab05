cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(banking)

set(LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/banking/Transaction.cpp ${CMAKE_CURRENT_SOURCE_DIR}/banking/Account.cpp)

add_library(${PROJECT_NAME} ${LIBRARIES})

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest>"
        "$<INSTALL_INTERFACE:third-party/gtest>"
        )

option(BUILD_TESTS "Builds tests" ON)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest)
  add_executable(tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)
  target_link_libraries(tests ${PROJECT_NAME} gtest_main)
  add_test(NAME unit_test COMMAND tests)
endif()

if(NOT H2D_REAL)
    return()
endif(NOT H2D_REAL)

project(test-tutorial-P05-02-eigenvalue-adapt)

add_executable(${PROJECT_NAME} main.cpp ../definitions.cpp)
include (${hermes2d_SOURCE_DIR}/CMake.common)
set_common_target_properties(${PROJECT_NAME})
set(BIN ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
add_test(test-tutorial-P05-02-eigenvalue-adapt ${BIN})
set_tests_properties(test-tutorial-P05-02-eigenvalue-adapt PROPERTIES LABELS slow)

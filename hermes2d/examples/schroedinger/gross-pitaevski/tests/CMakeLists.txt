if(NOT H2D_COMPLEX)
    return()
endif(NOT H2D_COMPLEX)
project(test-example-gross-pitaevski)

add_executable(${PROJECT_NAME} main.cpp ../definitions.cpp)
include (${hermes2d_SOURCE_DIR}/CMake.common)
set_common_target_properties(${PROJECT_NAME} ${HERMES2D_CPLX})
set(BIN ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
add_test(test-example-gross-pitaevski ${BIN})
set_tests_properties(test-example-gross-pitaevski PROPERTIES LABELS slow)


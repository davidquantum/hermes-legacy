project(test-tutorial-P08-30-nurbs)

add_executable(${PROJECT_NAME} main.cpp)
include (${hermes2d_SOURCE_DIR}/CMake.common)
set_common_target_properties(${PROJECT_NAME})
set(BIN ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
add_test(test-tutorial-P08-30-nurbs-1 ${BIN} 1)
add_test(test-tutorial-P08-30-nurbs-2 ${BIN} 2)
add_test(test-tutorial-P08-30-nurbs-3 ${BIN} 3)

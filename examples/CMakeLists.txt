set(RK_EXAMPLES_SOURCES ${RK_EXAMPLES_PATH}/hello.cpp)

add_executable(hello
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES})

add_dependencies(hello redkite)
target_link_libraries(hello redkite)
target_link_libraries(hello "-lrt -lm -ldl")



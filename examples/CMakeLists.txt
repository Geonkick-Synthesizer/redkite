set(RK_EXAMPLES_SOURCES ${RK_EXAMPLES_PATH}/hello.cpp)
set(RK_EXAMPLES_SOURCES_MULTI ${RK_EXAMPLES_PATH}/hello_multi.cpp)
set(RK_EXAMPLES_SOURCES_CHILD ${RK_EXAMPLES_PATH}/child.cpp)

add_executable(hello
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES})

add_dependencies(hello redkite)
target_link_libraries(hello redkite)
target_link_libraries(hello "-lX11 -lrt -lm -ldl")

add_executable(hello_multi
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_MULTI})

add_dependencies(hello_multi redkite)
target_link_libraries(hello_multi redkite)
target_link_libraries(hello_multi "-lX11 -lpthread -lrt -lm -ldl")

add_executable(child
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_CHILD})

add_dependencies(child redkite)
target_link_libraries(child redkite)
target_link_libraries(child "-lX11 -lrt -lm -ldl")




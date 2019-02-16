set(RK_EXAMPLES_SOURCES ${RK_EXAMPLES_PATH}/hello.cpp)
set(RK_EXAMPLES_SOURCES_MULTI ${RK_EXAMPLES_PATH}/hello_multi.cpp)
set(RK_EXAMPLES_SOURCES_CHILD ${RK_EXAMPLES_PATH}/child.cpp)
set(RK_EXAMPLES_SOURCES_PROPERTY ${RK_EXAMPLES_PATH}/property.cpp)
set(RK_EXAMPLES_SOURCES_LABEL ${RK_EXAMPLES_PATH}/label.cpp)
set(RK_EXAMPLES_SOURCES_WIDGET_COLORS ${RK_EXAMPLES_PATH}/widget_colors.cpp)

add_executable(hello
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES})

add_dependencies(hello redkite)
target_link_libraries(hello redkite)
target_link_libraries(hello "-lstdc++ -lm")

#add_executable(hello_multi
#  ${RK_HEADERS}
#  ${RK_EXAMPLES_SOURCES_MULTI})

#add_dependencies(hello_multi redkite)
#target_link_libraries(hello_multi redkite)
#target_link_libraries(hello_multi "-lX11 -lpthread -lrt -lm -ldl")

#add_executable(child
#  ${RK_HEADERS}
#  ${RK_EXAMPLES_SOURCES_CHILD})

#add_dependencies(child redkite)
#target_link_libraries(child redkite)
#target_link_libraries(child "-lX11 -lrt -lm -ldl")

#add_executable(property
#  ${RK_HEADERS}
#  ${RK_EXAMPLES_SOURCES_PROPERTY})

#add_dependencies(property redkite)
#target_link_libraries(property redkite)
#target_link_libraries(property "-lX11 -lrt -lm -ldl")

# ------------ Label Example -------

#add_executable(label
#  ${RK_HEADERS}
#  ${RK_EXAMPLES_SOURCES_LABEL})

#add_dependencies(label redkite)
#target_link_libraries(label redkite)
#target_link_libraries(label "-lX11 -lrt -lm -ldl")

#------------- Widget Colors --------

#add_executable(widget_colors
#  ${RK_HEADERS}
#  ${RK_EXAMPLES_SOURCES_WIDGET_COLORS})

#add_dependencies(widget_colors redkite)
#target_link_libraries(widget_colors redkite)
#target_link_libraries(widget_colors "-lX11 -lrt -lm -ldl")

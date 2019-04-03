set(RK_EXAMPLES_SOURCES ${RK_EXAMPLES_PATH}/hello.cpp)
set(RK_EXAMPLES_SOURCES_MULTI ${RK_EXAMPLES_PATH}/hello_multi.cpp)
set(RK_EXAMPLES_SOURCES_CHILD ${RK_EXAMPLES_PATH}/child.cpp)
set(RK_EXAMPLES_SOURCES_PROPERTY ${RK_EXAMPLES_PATH}/property.cpp)
set(RK_EXAMPLES_SOURCES_LABEL ${RK_EXAMPLES_PATH}/label.cpp)
set(RK_EXAMPLES_SOURCES_WIDGET_COLORS ${RK_EXAMPLES_PATH}/widget_colors.cpp)
set(RK_EXAMPLES_SOURCES_PAINTER ${RK_EXAMPLES_PATH}/painter.cpp)

if (MSVC)
  set(RK_EXEC_OPTION WIN32)
else()
  set(RK_EXEC_OPTION "")
endif()

if (RK_GRAPHICS_BACKEND MATCHES Cairo)
  set(RK_GRAPHICS_BACKEND_LINK_LIBS "-lcairo")
endif()

add_executable(hello ${RK_EXEC_OPTION}
	${RK_HEADERS}
	${RK_EXAMPLES_SOURCES})

add_dependencies(hello redkite)
target_link_libraries(hello redkite)
if (CMAKE_SYSTEM_NAME MATCHES Windows)
  target_link_libraries(hello "-mwindows -lstdc++ -lm -lmingw32")
  target_link_libraries(hello ${RK_GRAPHICS_BACKEND_LINK_LIBS})
else()
  target_link_libraries(hello "-lX11 -lpthread -lrt -lm -ldl")
  target_link_libraries(hello ${RK_GRAPHICS_BACKEND_LINK_LIBS})
endif()

# ------------ Multithreading Example -------

add_executable(hello_multi
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_MULTI})

add_dependencies(hello_multi redkite)
target_link_libraries(hello_multi redkite)
target_link_libraries(hello_multi "-lX11 -lpthread -lrt -lm -ldl")
target_link_libraries(hello_multi ${RK_GRAPHICS_BACKEND_LINK_LIBS})

# ------------ Child Example -------

add_executable(child ${RK_EXEC_OPTION}
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_CHILD})
add_dependencies(child redkite)
target_link_libraries(child redkite)
if (CMAKE_SYSTEM_NAME MATCHES Windows)
  target_link_libraries(child "-mwindows -lstdc++ -lm -lmingw32")
  target_link_libraries(child ${RK_GRAPHICS_BACKEND_LINK_LIBS})
else()
  target_link_libraries(child "-lX11 -lpthread -lrt -lm -ldl")
  target_link_libraries(child ${RK_GRAPHICS_BACKEND_LINK_LIBS})
endif()


# ------------ Property -------

add_executable(property
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_PROPERTY})

add_dependencies(property redkite)
target_link_libraries(property redkite)
target_link_libraries(property "-lX11 -lrt -lm -ldl")
target_link_libraries(property ${RK_GRAPHICS_BACKEND_LINK_LIBS})

# ------------ Label Example -------

add_executable(label
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_LABEL})

add_dependencies(label redkite)
target_link_libraries(label redkite)
target_link_libraries(label "-lX11 -lrt -lm -ldl")
target_link_libraries(label ${RK_GRAPHICS_BACKEND_LINK_LIBS})

#------------- Widget Colors --------

add_executable(widget_colors
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_WIDGET_COLORS})

add_dependencies(widget_colors redkite)
target_link_libraries(widget_colors redkite)
target_link_libraries(widget_colors "-lX11 -lrt -lm -ldl")
target_link_libraries(widget_colors ${RK_GRAPHICS_BACKEND_LINK_LIBS})

# ------------ Painter Ezmaple -------

add_executable(painter
  ${RK_HEADERS}
  ${RK_EXAMPLES_SOURCES_PAINTER})

add_dependencies(painter redkite)
target_link_libraries(painter redkite)
target_link_libraries(painter "-lX11 -lrt -lm -ldl")
target_link_libraries(painter ${RK_GRAPHICS_BACKEND_LINK_LIBS})


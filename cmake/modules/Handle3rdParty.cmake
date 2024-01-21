# Simple-Web-Server (#include <server_https.hpp> ...)
function(project_init_web_server)
  set(SIMPLE_WEB_SERVER_SRC ${PROJECT_DIR_3RD_PARTY}/Simple-Web-Server)
  add_subdirectory(${SIMPLE_WEB_SERVER_SRC})
endfunction()

function(project_init_c4core)
  set(C4CORE_SRC ${PROJECT_DIR_3RD_PARTY}/c4core)
  add_subdirectory(${C4CORE_SRC})
endfunction()

function(project_init_json)

  FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
  FetchContent_MakeAvailable(json)
endfunction()

function(project_init_backward)

  set(BACKWARDCPP_SRC ${PROJECT_DIR_3RD_PARTY}/backward-cpp)
  add_subdirectory(${BACKWARDCPP_SRC})
  message(STATUS "Stack Trace: ${STACK_TRACE_LEVEL} ")

  if(STACK_TRACE_LEVEL STREQUAL "Detailed")
    add_compile_definitions(STACK_TRACE_ENABLED=1)
    add_compile_definitions(STACK_TRACE_MINIMAL=0)
  elseif(STACK_TRACE_LEVEL STREQUAL "Minimal")
    add_compile_definitions(STACK_TRACE_ENABLED=1)
    add_compile_definitions(STACK_TRACE_MINIMAL=1)
  elseif(STACK_TRACE_LEVEL STREQUAL "Off")
    add_compile_definitions(STACK_TRACE_ENABLED=0)
  endif()

  # FetchContent_Declare( backward-cpp URL
  # https://github.com/bombela/backward-cpp/archive/refs/tags/v1.6.tar.gz #
  # SYSTEM # optional, the Backward include directory will be treated as #
  # system directory ) FetchContent_MakeAvailable(backward-cpp)
  #
  # FetchContent_GetProperties(backward-cpp) if(NOT backward-cpp_POPULATED)
  # FetchContent_Populate(backward-cpp) endif()
  # add_subdirectory(${backward-cpp_SOURCE_DIR} ${backward-cpp_BINARY_DIR} )

endfunction()

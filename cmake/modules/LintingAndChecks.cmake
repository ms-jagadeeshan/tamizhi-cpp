function(project_add_clang)

  file(GLOB_RECURSE _sources_and_headers_src "${PROJECT_DIR_SRC}/*.h"
       "${PROJECT_DIR_SRC}/*.tcc" "${PROJECT_DIR_SRC}/*.cpp"
       "${PROJECT_DIR_SRC}/*.hpp")

  list(FILTER _sources_and_headers_src EXCLUDE REGEX
       "${PROJECT_DIR_SRC}/core/core/")

  if(NOT WIN32)
    find_program(CLANG_FORMAT_EXECUTABLE clang-format
                 PATHS /usr/lib/llvm-6.0/bin/clang-format)
    if(CLANG_FORMAT_EXECUTABLE)
      message(STATUS "Running clang-format on source files")
      execute_process(COMMAND ${CLANG_FORMAT_EXECUTABLE} -style=file -i
                              ${_sources_and_headers_src})
    else()
      message(
        STATUS "Clang-format not found, skipping clang-format custom target")
    endif()
  endif()
endfunction()

function(linting_and_checks)
  project_add_clang()
endfunction()

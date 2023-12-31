include(FetchContent)

function(check_required_submodules)
  if(NOT EXISTS "${PROJECT_DIR_DATA}/.git")
    message(FATAL_ERROR "data submodule is not available, Please run
    git submodule update --init --recursive")
  endif()

  if(NOT EXISTS "${PROJECT_DIR_3RD_PARTY}/.git")
    message(FATAL_ERROR "3rd party submodule is not available. Please run
     git submodule update --init --recursive")
  endif()

endfunction()

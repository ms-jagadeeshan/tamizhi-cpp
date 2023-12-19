# ##############################################################################
# Convenience function to get the name of the current CMake source directory
# project_get_directory_name(<output variable>)
function(project_get_directory_name _out_name)
  get_filename_component(_curr_directory_name "${CMAKE_CURRENT_SOURCE_DIR}"
                         NAME)
  set(${_out_name}
      ${_curr_directory_name}
      PARENT_SCOPE)
endfunction()

# ##############################################################################
# Retrieves the current target name from the name of the current directory, and
# stores the result in _out_target_name project_get_target_name(<output
# variable>)
function(project_get_target_name _out_target_name)
  project_get_directory_name(_curr_directory_name)
  set(${_out_target_name}
      ${_curr_directory_name}
      PARENT_SCOPE)
endfunction()

# ##############################################################################
# Convenience function to retrieve subdirectories of the current directory
# project_get_subdirectory_list(<output variable>)
function(project_get_subdirectory_list _out_list)
  file(GLOB _all_children *)

  # message(STATUS "all children: ${_all_children}")
  foreach(_child IN ITEMS ${_all_children})
    if(IS_DIRECTORY ${_child})
      list(APPEND _result ${_child})
    endif()
  endforeach()

  # message(STATUS "subdirectories: ${_result}")
  set(${_out_list}
      ${_result}
      PARENT_SCOPE)
endfunction()

# ##############################################################################
# Given a list of file paths (absolute or relative), adds each file to a source
# group (Visual Studio filter directory) such that the source group matches the
# folder path relative to the specified _root_path
#
# * Adapted from answer in
#   http://stackoverflow.com/questions/31422680/how-to-set-visual-studio-filters-for-nested-sub-directory-using-cmake
function(project_assign_source_group _root_path _group_prefix)
  foreach(_source IN ITEMS ${ARGN})
    # Get relative directory path
    if(IS_ABSOLUTE "${_source}")
      file(RELATIVE_PATH _source_rel "${_root_path}" "${_source}")
    else()
      set(_source_rel "${_source}")
    endif()

    get_filename_component(_source_path "${_source_rel}" DIRECTORY)

    set(_source_path "${_group_prefix}${_source_path}")

    # source_group requires double backslashes
    string(REPLACE "/" "\\" _source_path_replaced "${_source_path}")
    source_group("${_source_path_replaced}" FILES "${_source}")
    # message("Adding ${_source} to ${_source_path_replaced}")
  endforeach()
endfunction()

# ##############################################################################
# Utility function to get the list of source and header.
# project_add_prep(<output variable>)
function(project_add_prep _out_sources_and_headers)
  project_get_target_name(_curr_target_name)

  set_property(GLOBAL APPEND PROPERTY PROJECT_TARGETS ${_target_name})

  file(
    GLOB
    _sources_and_headers
    "*.h"
    "*.hpp"
    "*.tcc"
    "*.cpp"
    "*.cxx")

  file(GLOB _headers "*.h " "*.hpp" "*.tcc")

  project_get_subdirectory_list(_subdirectory_list)

  # message("subdirectories: ${_subdirectory_list}")
  foreach(_subdirectory IN ITEMS ${_subdirectory_list})
    get_filename_component(_subdirectory_name ${_subdirectory} NAME)

    if(NOT EXISTS ${_subdirectory}/CMakeLists.txt)
      file(
        GLOB_RECURSE
        _this_glob
        "${_subdirectory_name}/*.h"
        "${_subdirectory_name}/*.hpp"
        "${_subdirectory_name}/*.tcc"
        "${_subdirectory_name}/*.cpp"
        "${_subdirectory_name}/*.cxx")

      file(GLOB_RECURSE _this_glob_header "${_subdirectory_name}/*.h "
           "${_subdirectory_name}/*.hpp" "${_subdirectory_name}/*.tcc")

      list(APPEND _sources_and_headers ${_this_glob})
      list(APPEND _headers ${_this_glob_header})
    endif()
  endforeach()

  # Need to look into this. source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
  # ${_sources_and_headers}) source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
  # ${_headers})
  project_assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} ""
                              ${_sources_and_headers})
  project_assign_source_group(${CMAKE_CURRENT_SOURCE_DIR} "" ${_headers})

  set(${_out_sources_and_headers}
      ${_sources_and_headers}
      PARENT_SCOPE)
  set(${_out_headers}
      ${_headers}
      PARENT_SCOPE)
endfunction()

# ##############################################################################
# Convenience function of add_library project_add_library()
function(project_add_library)
  project_get_target_name(_target_name)
  project_add_prep(_sources_and_headers)

  # message(STATUS "Adding library ${_target_name}") message(STATUS "  Sources:
  # ${_sources_and_headers}")
  add_library(${_target_name} ${_sources_and_headers})
  set_target_properties(${_target_name} PROPERTIES LINKER_LANGUAGE CXX)
  if(NEED_LINKING_AGAINST_LIBM)
    target_link_libraries(${_target_name} m)
  endif()
endfunction()

# ##############################################################################
# Check if the target is buildable or not project_is_target_buildable()
function(project_is_target_buildable _result)
  project_get_target_name(_target_name)
  if(NOT TARGET ${_target_name})
    return()
  endif()

  set(_result_local ON)

  set(${_out_build}
      ${_out_build_local}
      PARENT_SCOPE)
endfunction()

# ##############################################################################
# Continue CMake processing on any immediate subdirectories constaining
# CMakeLists.txt project_add_subdirectories()
function(project_add_subdirectories)
  project_get_target_name(_target_name)

  project_is_target_buildable(_BUILD_TARGET)
  if(NOT ${_BUILD_TARGET})
    return()
  endif()

  project_get_subdirectory_list(_subdirectory_list)
  foreach(_subdirectory IN ITEMS ${_subdirectory_list})
    if(EXISTS ${_subdirectory}/CMakeLists.txt)
      add_subdirectory(${_subdirectory})
    endif()
  endforeach()
endfunction()

# ##############################################################################
# Convenience function to append a value to a target's property
# project_append_target_property(<target name> <property name> [<element> ...])
function(project_append_target_property _target_name _property_name)
  get_target_property(_property ${_target_name} ${_property_name})

  if(_property)
    list(APPEND _property ${ARGN})
  else()
    set(_property ${ARGN})
  endif()

  set_target_properties(${_target_name} PROPERTIES ${_property_name}
                                                   "${_property}")
endfunction()

# ##############################################################################
# Runs target_link_libraries on a target with the current directory name.
# project_target_link_libraries(<dependency name(s)> <additional optional
# params>)
function(project_target_link_libraries)
  project_get_target_name(_target_name)

  project_is_target_buildable(_BUILD_TARGET)
  if(NOT ${_BUILD_TARGET})
    return()
  endif()

  foreach(_other_target IN ITEMS ${ARGN})
    if(${_other_target} STREQUAL "DESKTOP")
      if(${BUILD_SERVER})
        return()
      else()
        continue()
      endif()
    endif()

    target_link_libraries(${_target_name} ${_other_target})

    # Skip public/private/interface keywords WARNING: This is not a complete
    # solution, and other keywords are permitted in target_link_libraries. May
    # need to revisit this.
    if(${_other_target} STREQUAL "PUBLIC"
       OR ${_other_target} STREQUAL "INTERFACE"
       OR ${_other_target} STREQUAL "PRIVATE")
      continue()
    endif()
    project_append_target_property(${_target_name} PROJECT_DEPENDENCY_TARGETS
                                   ${_other_target})
    get_target_property(_dependency_targets ${_target_name}
                        PROJECT_DEPENDENCY_TARGETS)
  endforeach()
endfunction()

# ##############################################################################
# Utility function for project_add_executable
# project_add_executable_prep(<is_unit_test>)
function(project_add_executable_prep _is_unit_test)
  project_get_target_name(_target_name)

  project_add_prep(_sources_and_headers ${ARGN})
  project_get_target_name(_target_name)
  set_property(GLOBAL APPEND PROPERTY PROJECT_EXECUTABLE_TARGETS
                                      ${_target_name})

  add_executable(${_target_name} ${_sources_and_headers})

  get_property(_install_targets GLOBAL PROPERTY PROJECT_INSTALL_TARGETS)

  if(${_target_name} IN_LIST _install_targets)
    install(TARGETS ${_target_name} DESTINATION ${PROJECT_INSTALL_DIRECTORY})
  endif()
endfunction()

# ##############################################################################
# Creates an executable project for all source and header files in the current
# directory. project_add_executable()
function(project_add_executable)
  project_get_target_name(_target_name)
  project_add_executable_prep(FALSE ${ARGN})
  project_get_target_name(_target_name)

  set_target_properties(PROPERTIES FOLDER Apps)
  set_property(TARGET ${_target_name} PROPERTY ENABLE_EXPORTS ON)

endfunction()

# ##############################################################################
# Creates an example project for all source and header files in the current
# directory. project_add_example()
function(project_add_example)

  project_get_target_name(_target_name)
  if(NOT BUILD_EXAMPLES)
    add_custom_target(${_target_name})
    project_add_property(INTERFACE_EXAMPLE)
    return()
  endif()

  project_add_executable_prep(FALSE ${ARGN})
  project_get_target_name(_target_name)

  # Store the debug information for debugging.
  set_target_properties(PROPERTIES FOLDER Apps)
  set_property(TARGET ${_target_name} PROPERTY ENABLE_EXPORTS ON)
  # set_property(TARGET ${_target_name} PROPERTY EXCLUDE_FROM_ALL 1 )
  # set_property(TARGET ${_target_name} PROPERTY EXCLUDE_FROM_DEFAULT_BUILD 1)
endfunction()

# ##############################################################################
# Creates an unit test project for all source and header files in the current
# directory. project_add_unit_tests()
function(project_add_unit_tests)

  project_get_target_name(_target_name)
  foreach(_item ${ARGN})
    # Add a dummy target, add a property to it and then return.
    if(_item STREQUAL "DESKTOP" AND BUILD_SERVER)
      add_custom_target(${_target_name})
      project_add_property(INTERFACE_DESKTOP)
      return()
    endif()
  endforeach()

  project_add_executable_prep(TRUE ${ARGN})

  # Add post-build event to run tests
  project_run_target_on_post_build()

  # project_target_link_libraries(coreTest)
  set_target_properties(${_target_name} PROPERTIES FOLDER UnitTests)
endfunction()

# ##############################################################################
# Executes the target executable after it's built, and fails the build if the
# execution fails (eg. for unit tests) project_run_target_on_post_build()
function(project_run_target_on_post_build)

  if(BUILD_UNIT_TESTS)
    project_get_target_name(_target_name)
    add_custom_command(
      TARGET ${_target_name}
      POST_BUILD
      COMMAND ${_target_name}})
  endif()
endfunction()

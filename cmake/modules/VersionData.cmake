function(get_git_commit_hash OUTPUT_VARIABLE)
    find_package(Git)

    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE GIT_RESULT
            OUTPUT_VARIABLE GIT_COMMIT_HASH
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        if(GIT_RESULT EQUAL 0)
            set(${OUTPUT_VARIABLE} ${GIT_COMMIT_HASH} PARENT_SCOPE)
        else()
            message(WARNING "Not a Git repository. Setting commit hash to '000000'.")
            set(${OUTPUT_VARIABLE} "000000" PARENT_SCOPE)
        endif()
    else()
        message(WARNING "Git not found. Unable to retrieve commit hash. Setting to '000000'.")
        set(${OUTPUT_VARIABLE} "000000" PARENT_SCOPE)
    endif()
endfunction()


# Function to configure version and commit hash into a header file
function(setup_version_file)
  message(STATUS "Configuring version information...")
  # Get Git commit hash
  get_git_commit_hash(PROJECT_GIT_COMMIT_HASH)
  message(STATUS "Git commit hash: ${PROJECT_GIT_COMMIT_HASH}")

  # Configure VersionData.h
 	set(INPUT_FILE "${PROJECT_DIR_CMAKE}/buildFiles/VersionData.h.in")
	set(OUTPUT_FILE "${PROJECT_DIR_SRC}/core/version/VersionData.h")

  file(REMOVE "${OUTPUT_FILE}")
  configure_file(${INPUT_FILE} ${OUTPUT_FILE})
endfunction()





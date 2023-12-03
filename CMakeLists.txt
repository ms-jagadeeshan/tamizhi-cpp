# Set Minimum cmake version
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# Set project version
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
math(EXPR PROJECT_VERSION_NUMERIC "10000 * ${PROJECT_VERSION_MAJOR} + 100 * ${PROJECT_VERSION_MINOR} + ${PROJECT_VERSION_PATCH}")
set(PROJECT_VERSION_STRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

# Absolute Path to common directories
set(PROJECT_DIR_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root directory" FORCE)
set(PROJECT_DIR_CMAKE ${PROJECT_DIR_ROOT}/cmake CACHE STRING "Root 'CMake' directory" FORCE)
set(PROJECT_DIR_CMAKE_MODULES ${PROJECT_DIR_CMAKE}/modules CACHE STRING "CMake modules directory" FORCE)
set(PROJECT_DIR_SRC ${PROJECT_DIR_ROOT}/tamizhi CACHE STRING "Root 'Src' directory" FORCE)
set(PROJECT_DIR_DATA ${PROJECT_DIR_ROOT}/data CACHE STRING "Root 'Src' directory" FORCE)
set(PROJECT_DIR_BUILD ${PROJECT_DIR_ROOT}/build CACHE STRING "Root 'Build' directory" FORCE)
set(PROJECT_DIR_LIB ${CMAKE_BINARY_DIR}/lib CACHE STRING "Root 'lib' directory" FORCE)
set(PROJECT_DIR_BIN ${CMAKE_BINARY_DIR}/bin CACHE STRING "Root 'bin' directory" FORCE)
set(PROJECT_DIR_INCLUDE ${CMAKE_BINARY_DIR}/include CACHE STRING "Root 'Include' directory" FORCE)
set(PROJECT_DIR_LOG ${CMAKE_BINARY_DIR}/logs CACHE STRING "Root 'logs' directory" FORCE)
set(PROJECT_DIR_INSTALL ${PROJECT_DIR_ROOT} CACHE STRING "Install directory" FORCE)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_DIR_CMAKE_MODULES})

# Set project name
project(TAMIZHI LANGUAGES CXX C
  VERSION ${PROJECT_VERSION_STRING})

include(VersionData)
include(HandleOptions)
include(HandleCompilationFlags)
include(LintingAndChecks)
include(ProjectUtils)
include(PathData)

# Project Initialization
set_flags()
setup_path_file()
setup_version_file()

if(LINT_SOURCE)
  linting_and_checks() 
endif()


include_directories(${PROJECT_DIR_ROOT})
# SRC directory (typical include)
include_directories(${PROJECT_DIR_SRC}) 


# Add Components
add_subdirectory(tamizhi)


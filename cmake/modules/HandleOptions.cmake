# General options
option(FORCE_SHARED_LIB
       "Force tamizhi to be a shared library, overriding BUILD_SHARED_LIBS" ON)
option(FORCE_STATIC_LIB
       "Force tamizhi to be a static library, overriding BUILD_SHARED_LIBS" OFF)
option(BUILD_PYTHON
       "Enable/Disable building & installation of Python module with pybind11"
       OFF)
option(BUILD_DOCS "Build documentation" ON)
option(BUILD_EXAMPLES "Build Examples" ON)
option(BUILD_UNIT_TESTS "Build Unit Tests" ON)
option(LINT_SOURCE "Lint sources" ON)
set(PYTHON_VERSION
    "Default"
    CACHE STRING "The version of Python to build the wrappers against.")

# Compilation options
option(ENABLE_MEMORY_SANITIZER "Enable/Disable memory sanitizer" OFF)
option(ENABLE_PROFILER "Enable profiling with gperftools" OFF)

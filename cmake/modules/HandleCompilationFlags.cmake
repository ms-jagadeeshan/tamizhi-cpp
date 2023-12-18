
macro(set_flags)
  if(NOT MSVC)
    include(CheckCXXCompilerFlag)
    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      check_cxx_compiler_flag(-std=c++17 SUPPORTS_CXX17)
      if(NOT SUPPORTS_CXX17)
        message(FATEL_ERROR "Compiler doesn't support C++17")
      endif()
    else()
      set(CMAKE_C_COMPILER "/usr/bin/gcc")
			set(CMAKE_CXX_COMPILER "/usr/bin/gcc")
			check_cxx_compiler_flag(-std=c++17 SUPPORTS_CXX17)
			if(NOT SUPPORTS_CXX17)
				message(FATAL_ERROR "Compiler doesn't support C++17")
			endif()
    endif()

  endif()

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_EXTENSIONS OFF)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	set(MAKEFLAGS ${MAKEFLAGS}:${MAKE_TURNOFF_PRINT_DIRECTORY})
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

  message("CMake Build Type: ${CMAKE_BUILD_TYPE}")
  # set(CMAKE_BUILD_TYPE "Debug")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-O2)
    add_link_options(-O2)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
  else()
    message("Applying O3 optimization")
    add_compile_options(-O3)
    add_link_options(-O3)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
  endif()

  if(ENABLE_PROFILER)
    find_package(Gperftools COMPONENTS tcmalloc OPTIONAL_COMPONENTS profiler)

    if(GPERFTOOLS_FOUND)
      add_definitions(-DENABLE_PROFILING)
      add_link_options(-lprofiler)
    endif()
  endif()

  if(ENABLE_MEMORY_SANITIZER)
    add_compile_options(-fsanitize=address)
		add_link_options(-fsanitize=address)
		add_compile_options(-fno-omit-frame-pointer)
		add_link_options(-fno-omit-frame-pointer)
  endif()

  if(NOT MSVC)
    # Warnings as errors and all common warnings
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    # Disable warnings for deprecated declarations
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    # Warn on unused parameters
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter")
  endif()

endmacro()

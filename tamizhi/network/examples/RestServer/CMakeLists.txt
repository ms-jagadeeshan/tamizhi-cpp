find_package(Libunwind REQUIRED)
project_add_example()
project_target_link_libraries(core)

# project_target_link_libraries(Backward::Backward)

target_include_directories(RestServer PRIVATE ${LIBUNWIND_INCLUDE_DIR})
# target_include_directories( RestServer PRIVATE
# /home/jaga-matrix/Downloads/out/learning/tmp/master_tmp/fleet_core/external/libunwind/x86_64.linux/include
# )
target_link_libraries(RestServer ${LIBUNWIND_LIBRARIES})
# target_link_libraries( RestServer
# /home/jaga-matrix/Downloads/out/learning/tmp/master_tmp/fleet_core/external/libunwind/x86_64.linux/lib/libunwind.so.8.0.1
# ) project_target_link_libraries(unwind)
project_target_link_libraries(network)

macro(setup_path_file)
  set(INPUT_FILE "${PROJECT_DIR_CMAKE}/buildFiles/ConfigPath.h.in")
  set(OUTPUT_FILE "${PROJECT_DIR_SRC}/core/file/ConfigPath.h")

  file(REMOVE "${OUTPUT_FILE}")
  configure_file(${INPUT_FILE} ${OUTPUT_FILE})

  # file(MAKE_DIRECTORY ${PROJECT_DIR_RUN_LOGS})
endmacro()

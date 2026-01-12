# The following variables contains the files used by the different stages of the build process.
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_assemble)
set_source_files_properties(${Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_compile "${CMAKE_CURRENT_SOURCE_DIR}/../../../main.c")
set_source_files_properties(${Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_compile_cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/core/AbstractModule.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/relay/relay_module.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/servo/ServoModule.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/servo/servo_module.cpp")
set_source_files_properties(${Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_link)
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_objcopy_ihex)
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_objcopy_eep)
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_objcopy_lss)
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_objcopy_srec)
set(Servo_Simulator_default_default_AVR_GCC_FILE_TYPE_objcopy_sig)
set(Servo_Simulator_default_image_name "firmware.elf")
set(Servo_Simulator_default_image_base_name "firmware")

# The output directory of the final image.
set(Servo_Simulator_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1")

# The full path to the final image.
set(Servo_Simulator_default_full_path_to_image ${Servo_Simulator_default_output_dir}/${Servo_Simulator_default_image_name})

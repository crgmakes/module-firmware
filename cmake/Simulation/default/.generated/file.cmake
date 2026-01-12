# The following variables contains the files used by the different stages of the build process.
set(Simulation_default_default_AVR_GCC_FILE_TYPE_assemble)
set_source_files_properties(${Simulation_default_default_AVR_GCC_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Simulation_default_default_AVR_GCC_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Simulation_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${Simulation_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Simulation_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Simulation_default_default_AVR_GCC_FILE_TYPE_compile)
set_source_files_properties(${Simulation_default_default_AVR_GCC_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(Simulation_default_default_AVR_GCC_FILE_TYPE_compile_cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/relay/Adafruit BusIO/Adafruit_BusIO_Register.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/relay/Adafruit BusIO/Adafruit_GenericDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/relay/Adafruit BusIO/Adafruit_I2CDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/relay/Adafruit BusIO/Adafruit_SPIDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/core/AbstractModule.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/servo/ServoModule.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/servo/servo_module.cpp")
set_source_files_properties(${Simulation_default_default_AVR_GCC_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(Simulation_default_default_AVR_GCC_FILE_TYPE_link
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib04b/libWire.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib205/libServo_megaTinyCore.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib713/libSPI.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib9ae/libAdafruit BusIO.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/libFrameworkArduino.a")
set(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_ihex)
set(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_eep)
set(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_lss)
set(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_srec)
set(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_sig)
set(Simulation_default_image_name "firmware.elf")
set(Simulation_default_image_base_name "firmware")

# The output directory of the final image.
set(Simulation_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1")

# The full path to the final image.
set(Simulation_default_full_path_to_image ${Simulation_default_output_dir}/${Simulation_default_image_name})

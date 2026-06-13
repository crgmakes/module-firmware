# The following variables contains the files used by the different stages of the build process.
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_assemble)
set_source_files_properties(${Firmware_servo_default_AVR_GCC_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Firmware_servo_default_AVR_GCC_FILE_TYPE_assemble})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Firmware_servo_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/wiring_pulse.S")
set_source_files_properties(${Firmware_servo_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)

# For assembly files, add "." to the include path for each file so that .include with a relative path works
foreach(source_file ${Firmware_servo_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess})
        set_source_files_properties(${source_file} PROPERTIES INCLUDE_DIRECTORIES "$<PATH:NORMAL_PATH,$<PATH:REMOVE_FILENAME,${source_file}>>")
endforeach()

set(Firmware_servo_default_AVR_GCC_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/WInterrupts.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/WInterrupts_PA.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/WInterrupts_PB.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/WInterrupts_PC.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/hooks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/wiring.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/wiring_analog.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/wiring_digital.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/wiring_pulse.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/wiring_shift.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Wire/src/twi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Wire/src/twi_pins.c")
set_source_files_properties(${Firmware_servo_default_AVR_GCC_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_compile_cpp
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/ExtraWiring.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/Tone.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/UART.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/UART0.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/UART1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/WMath.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/abi.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/api/Common.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/api/IPAddress.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/api/PluggableUSB.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/api/Print.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/api/RingBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/api/Stream.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/api/String.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/new.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/cores/megatinycore/wiring_extra.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Comparator/src/Comparator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Comparator/src/ComparatorISR.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Event/src/Event.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Logic/src/Logic.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Logic/src/LogicISR.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Optiboot_flasher/src/Flash.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Optiboot_flasher/src/optiboot.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/SD/src/File.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/SD/src/SD.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/SD/src/utility/Sd2Card.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/SD/src/utility/SdFile.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/SD/src/utility/SdVolume.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/SPI/src/SPI.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Servo/src/megaavr/Servo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Servo_megaTinyCore/src/megaavr/Servo_megaTinyCore.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/SoftwareSerial/src/SoftwareSerial.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/Wire/src/Wire.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/megaTinyCore/src/ADCErrors.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/tinyNeoPixel/tinyNeoPixel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../.platformio/packages/framework-arduino-megaavr-megatinycore/libraries/tinyNeoPixel_Static/tinyNeoPixel_Static.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/servo1_1/Adafruit BusIO/Adafruit_BusIO_Register.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/servo1_1/Adafruit BusIO/Adafruit_GenericDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/servo1_1/Adafruit BusIO/Adafruit_I2CDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/libdeps/servo1_1/Adafruit BusIO/Adafruit_SPIDevice.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/core/AbstractModule.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/servo/ServoModule.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/servo/servo_module.cpp")
set_source_files_properties(${Firmware_servo_default_AVR_GCC_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_link
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib04b/libWire.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib205/libServo_megaTinyCore.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib713/libSPI.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/lib9ae/libAdafruit BusIO.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1/libFrameworkArduino.a")
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_ihex)
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_eep)
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_lss)
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_srec)
set(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_sig)
set(Firmware_servo_image_name "firmware.elf")
set(Firmware_servo_image_base_name "firmware")

# The output directory of the final image.
set(Firmware_servo_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../.pio/build/servo1_1")

# The full path to the final image.
set(Firmware_servo_full_path_to_image ${Firmware_servo_output_dir}/${Firmware_servo_image_name})

# Potential output file extensions
set(output_extensions
    .hex
    .lss
    .eep
    .srec
    .usersignatures)
list(TRANSFORM output_extensions PREPEND "${Firmware_servo_output_dir}/${Firmware_servo_image_base_name}")

# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Firmware_servo_library_list )

# Handle files with suffix s, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_assemble)
add_library(Firmware_servo_default_AVR_GCC_assemble OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_assemble})
    Firmware_servo_default_AVR_GCC_assemble_rule(Firmware_servo_default_AVR_GCC_assemble)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_assemble>")

endif()

# Handle files with suffix S, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess)
add_library(Firmware_servo_default_AVR_GCC_assembleWithPreprocess OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess})
    Firmware_servo_default_AVR_GCC_assembleWithPreprocess_rule(Firmware_servo_default_AVR_GCC_assembleWithPreprocess)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_compile)
add_library(Firmware_servo_default_AVR_GCC_compile OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_compile})
    Firmware_servo_default_AVR_GCC_compile_rule(Firmware_servo_default_AVR_GCC_compile)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_compile>")

endif()

# Handle files with suffix cpp, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_compile_cpp)
add_library(Firmware_servo_default_AVR_GCC_compile_cpp OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_compile_cpp})
    Firmware_servo_default_AVR_GCC_compile_cpp_rule(Firmware_servo_default_AVR_GCC_compile_cpp)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_compile_cpp>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_ihex)
add_library(Firmware_servo_default_AVR_GCC_objcopy_ihex OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_ihex})
    Firmware_servo_default_AVR_GCC_objcopy_ihex_rule(Firmware_servo_default_AVR_GCC_objcopy_ihex)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_objcopy_ihex>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_eep)
add_library(Firmware_servo_default_AVR_GCC_objcopy_eep OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_eep})
    Firmware_servo_default_AVR_GCC_objcopy_eep_rule(Firmware_servo_default_AVR_GCC_objcopy_eep)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_objcopy_eep>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_lss)
add_library(Firmware_servo_default_AVR_GCC_objcopy_lss OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_lss})
    Firmware_servo_default_AVR_GCC_objcopy_lss_rule(Firmware_servo_default_AVR_GCC_objcopy_lss)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_objcopy_lss>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_srec)
add_library(Firmware_servo_default_AVR_GCC_objcopy_srec OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_srec})
    Firmware_servo_default_AVR_GCC_objcopy_srec_rule(Firmware_servo_default_AVR_GCC_objcopy_srec)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_objcopy_srec>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_sig)
add_library(Firmware_servo_default_AVR_GCC_objcopy_sig OBJECT ${Firmware_servo_default_AVR_GCC_FILE_TYPE_objcopy_sig})
    Firmware_servo_default_AVR_GCC_objcopy_sig_rule(Firmware_servo_default_AVR_GCC_objcopy_sig)
    list(APPEND Firmware_servo_library_list "$<TARGET_OBJECTS:Firmware_servo_default_AVR_GCC_objcopy_sig>")

endif()


# Main target for this project
add_executable(Firmware_servo_image__RgkSZSs ${Firmware_servo_library_list})

set_target_properties(Firmware_servo_image__RgkSZSs PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Firmware_servo_output_dir})
set_target_properties(Firmware_servo_image__RgkSZSs PROPERTIES OUTPUT_NAME "firmware")
set_target_properties(Firmware_servo_image__RgkSZSs PROPERTIES SUFFIX ".elf")

target_link_libraries(Firmware_servo_image__RgkSZSs PRIVATE ${Firmware_servo_default_AVR_GCC_FILE_TYPE_link})

#Add objcopy steps
Firmware_servo_objcopy_ihex_rule(Firmware_servo_image__RgkSZSs)
Firmware_servo_objcopy_eep_rule(Firmware_servo_image__RgkSZSs)
Firmware_servo_objcopy_lss_rule(Firmware_servo_image__RgkSZSs)
Firmware_servo_objcopy_srec_rule(Firmware_servo_image__RgkSZSs)
Firmware_servo_objcopy_sig_rule(Firmware_servo_image__RgkSZSs)

# Add the link options from the rule file.
Firmware_servo_link_rule(Firmware_servo_image__RgkSZSs)




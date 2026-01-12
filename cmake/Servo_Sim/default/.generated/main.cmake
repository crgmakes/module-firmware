# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Servo_Sim_default_library_list )

# Handle files with suffix s, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_assemble)
add_library(Servo_Sim_default_default_AVR_GCC_assemble OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_assemble})
    Servo_Sim_default_default_AVR_GCC_assemble_rule(Servo_Sim_default_default_AVR_GCC_assemble)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_assemble>")

endif()

# Handle files with suffix S, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess)
add_library(Servo_Sim_default_default_AVR_GCC_assembleWithPreprocess OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess})
    Servo_Sim_default_default_AVR_GCC_assembleWithPreprocess_rule(Servo_Sim_default_default_AVR_GCC_assembleWithPreprocess)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_compile)
add_library(Servo_Sim_default_default_AVR_GCC_compile OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_compile})
    Servo_Sim_default_default_AVR_GCC_compile_rule(Servo_Sim_default_default_AVR_GCC_compile)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_compile>")

endif()

# Handle files with suffix cpp, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_compile_cpp)
add_library(Servo_Sim_default_default_AVR_GCC_compile_cpp OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_compile_cpp})
    Servo_Sim_default_default_AVR_GCC_compile_cpp_rule(Servo_Sim_default_default_AVR_GCC_compile_cpp)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_compile_cpp>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_ihex)
add_library(Servo_Sim_default_default_AVR_GCC_objcopy_ihex OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_ihex})
    Servo_Sim_default_default_AVR_GCC_objcopy_ihex_rule(Servo_Sim_default_default_AVR_GCC_objcopy_ihex)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_objcopy_ihex>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_eep)
add_library(Servo_Sim_default_default_AVR_GCC_objcopy_eep OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_eep})
    Servo_Sim_default_default_AVR_GCC_objcopy_eep_rule(Servo_Sim_default_default_AVR_GCC_objcopy_eep)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_objcopy_eep>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_lss)
add_library(Servo_Sim_default_default_AVR_GCC_objcopy_lss OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_lss})
    Servo_Sim_default_default_AVR_GCC_objcopy_lss_rule(Servo_Sim_default_default_AVR_GCC_objcopy_lss)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_objcopy_lss>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_srec)
add_library(Servo_Sim_default_default_AVR_GCC_objcopy_srec OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_srec})
    Servo_Sim_default_default_AVR_GCC_objcopy_srec_rule(Servo_Sim_default_default_AVR_GCC_objcopy_srec)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_objcopy_srec>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_sig)
add_library(Servo_Sim_default_default_AVR_GCC_objcopy_sig OBJECT ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_objcopy_sig})
    Servo_Sim_default_default_AVR_GCC_objcopy_sig_rule(Servo_Sim_default_default_AVR_GCC_objcopy_sig)
    list(APPEND Servo_Sim_default_library_list "$<TARGET_OBJECTS:Servo_Sim_default_default_AVR_GCC_objcopy_sig>")

endif()


# Main target for this project
add_executable(Servo_Sim_default_image__RgkSZSs ${Servo_Sim_default_library_list})

set_target_properties(Servo_Sim_default_image__RgkSZSs PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Servo_Sim_default_output_dir})
set_target_properties(Servo_Sim_default_image__RgkSZSs PROPERTIES OUTPUT_NAME "firmware")
set_target_properties(Servo_Sim_default_image__RgkSZSs PROPERTIES SUFFIX ".elf")

target_link_libraries(Servo_Sim_default_image__RgkSZSs PRIVATE ${Servo_Sim_default_default_AVR_GCC_FILE_TYPE_link})

#Add objcopy steps
Servo_Sim_default_objcopy_ihex_rule(Servo_Sim_default_image__RgkSZSs)
Servo_Sim_default_objcopy_eep_rule(Servo_Sim_default_image__RgkSZSs)
Servo_Sim_default_objcopy_lss_rule(Servo_Sim_default_image__RgkSZSs)
Servo_Sim_default_objcopy_srec_rule(Servo_Sim_default_image__RgkSZSs)
Servo_Sim_default_objcopy_sig_rule(Servo_Sim_default_image__RgkSZSs)

# Add the link options from the rule file.
Servo_Sim_default_link_rule(Servo_Sim_default_image__RgkSZSs)




# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Simulation_default_library_list )

# Handle files with suffix s, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_assemble)
add_library(Simulation_default_default_AVR_GCC_assemble OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_assemble})
    Simulation_default_default_AVR_GCC_assemble_rule(Simulation_default_default_AVR_GCC_assemble)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_assemble>")

endif()

# Handle files with suffix S, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess)
add_library(Simulation_default_default_AVR_GCC_assembleWithPreprocess OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_assembleWithPreprocess})
    Simulation_default_default_AVR_GCC_assembleWithPreprocess_rule(Simulation_default_default_AVR_GCC_assembleWithPreprocess)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_assembleWithPreprocess>")

endif()

# Handle files with suffix [cC], for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_compile)
add_library(Simulation_default_default_AVR_GCC_compile OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_compile})
    Simulation_default_default_AVR_GCC_compile_rule(Simulation_default_default_AVR_GCC_compile)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_compile>")

endif()

# Handle files with suffix cpp, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_compile_cpp)
add_library(Simulation_default_default_AVR_GCC_compile_cpp OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_compile_cpp})
    Simulation_default_default_AVR_GCC_compile_cpp_rule(Simulation_default_default_AVR_GCC_compile_cpp)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_compile_cpp>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_ihex)
add_library(Simulation_default_default_AVR_GCC_objcopy_ihex OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_ihex})
    Simulation_default_default_AVR_GCC_objcopy_ihex_rule(Simulation_default_default_AVR_GCC_objcopy_ihex)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_objcopy_ihex>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_eep)
add_library(Simulation_default_default_AVR_GCC_objcopy_eep OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_eep})
    Simulation_default_default_AVR_GCC_objcopy_eep_rule(Simulation_default_default_AVR_GCC_objcopy_eep)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_objcopy_eep>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_lss)
add_library(Simulation_default_default_AVR_GCC_objcopy_lss OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_lss})
    Simulation_default_default_AVR_GCC_objcopy_lss_rule(Simulation_default_default_AVR_GCC_objcopy_lss)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_objcopy_lss>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_srec)
add_library(Simulation_default_default_AVR_GCC_objcopy_srec OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_srec})
    Simulation_default_default_AVR_GCC_objcopy_srec_rule(Simulation_default_default_AVR_GCC_objcopy_srec)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_objcopy_srec>")

endif()

# Handle files with suffix elf, for group default-AVR-GCC
if(Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_sig)
add_library(Simulation_default_default_AVR_GCC_objcopy_sig OBJECT ${Simulation_default_default_AVR_GCC_FILE_TYPE_objcopy_sig})
    Simulation_default_default_AVR_GCC_objcopy_sig_rule(Simulation_default_default_AVR_GCC_objcopy_sig)
    list(APPEND Simulation_default_library_list "$<TARGET_OBJECTS:Simulation_default_default_AVR_GCC_objcopy_sig>")

endif()


# Main target for this project
add_executable(Simulation_default_image__RgkSZSs ${Simulation_default_library_list})

set_target_properties(Simulation_default_image__RgkSZSs PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Simulation_default_output_dir})
set_target_properties(Simulation_default_image__RgkSZSs PROPERTIES OUTPUT_NAME "firmware")
set_target_properties(Simulation_default_image__RgkSZSs PROPERTIES SUFFIX ".elf")

target_link_libraries(Simulation_default_image__RgkSZSs PRIVATE ${Simulation_default_default_AVR_GCC_FILE_TYPE_link})

#Add objcopy steps
Simulation_default_objcopy_ihex_rule(Simulation_default_image__RgkSZSs)
Simulation_default_objcopy_eep_rule(Simulation_default_image__RgkSZSs)
Simulation_default_objcopy_lss_rule(Simulation_default_image__RgkSZSs)
Simulation_default_objcopy_srec_rule(Simulation_default_image__RgkSZSs)
Simulation_default_objcopy_sig_rule(Simulation_default_image__RgkSZSs)

# Add the link options from the rule file.
Simulation_default_link_rule(Simulation_default_image__RgkSZSs)




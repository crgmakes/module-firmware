# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/Users/tsasala/Development/Aquarius New/module-firmware/.pio/build/servo1_1/firmware.eep"
  "/Users/tsasala/Development/Aquarius New/module-firmware/.pio/build/servo1_1/firmware.hex"
  "/Users/tsasala/Development/Aquarius New/module-firmware/.pio/build/servo1_1/firmware.lss"
  "/Users/tsasala/Development/Aquarius New/module-firmware/.pio/build/servo1_1/firmware.srec"
  "/Users/tsasala/Development/Aquarius New/module-firmware/.pio/build/servo1_1/firmware.usersignatures"
  )
endif()

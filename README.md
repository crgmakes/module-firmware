# Module Firmware

This repository contains the firmware for Aquarius modules. Each module can be built from this single Platform IO project by selecting the appropriate environment from within Platform IO.

## Requirements

To program a module, you will need:
1. VS Code and Platform IO - see [how to](how_to_create_new_pio_project.md)
1. [UDPI programmer](https://www.adafruit.com/product/5879)
1. 6 pin header

or
 
1. Aquarius Module Programming Jig

## Install
1. Clone module-firmware
    - `git clone https://github.com/crgmakes/module-firmware.git`
1. Change to module-firmware library directory
    - `cd module-firmware/lib`
1. Clone Adafruit_seesawPeripheral
    - `git clone https://github.com/crgmakes/Adafruit_seesawPeripheral.git`

## Alternative Install
If you do not need to develop the Seesaw Peripheral library, then you can simply include it as a dependency.
To do so, uncomment the library in the platform.ini file after cloning the firmware repo.

```
lib_deps = 
	https://github.com/adafruit/Adafruit_BusIO.git
uncomment ->	; https://github.com/crgmakes/Adafruit_seesawPeripheral.git
	https://github.com/crgmakes/Adafruit_Seesaw.git
```

**NOTE: do *NOT* check in the platform.ini file!**


## Programming
1. Compile the appropriate environment
1. Attach programmer to your computer
1. Place programming header on target board or into programing jig
1. Click upload
1. Ensure programming is successful


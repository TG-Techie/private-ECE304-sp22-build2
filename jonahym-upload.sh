/Users/jonahym/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude \
    -C/Users/jonahym/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf \
    -v \
    -patmega328p \
    -carduino \
    -P/dev/cu.usbmodem145101 \
    -b115200 \
    -D \
    -Uflash:w:/var/folders/z1/91g4x4mn6xn2c7b9p_3l5jg80000gn/T/arduino_build_375722/sketch_apr21b.ino.hex:i 
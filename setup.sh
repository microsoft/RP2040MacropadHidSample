#!/bin/bash

echo -e "\n\n\tMicrosoft RP2040 LampArray Sample run\n\n"


echo -e "\n\tStep 2.\n"
sudo git clone https://github.com/microsoft/RP2040MacropadHidSample.git

echo -e "\n\tStep 3.\n"
sudo apt install build-essential

echo -e "\n\tStep 4\n"
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
sudo git clone https://github.com/raspberrypi/pico-sdk.git
sudo rm ./RP2040MacropadHidSample/src/pico_sdk_import.cmake
sudo cp ./pico-sdk/external/pico_sdk_import.cmake ./RP2040MacropadHidSample/src/pico_sdk_import.cmake
export PICO_SDK_PATH=$PWD/pico-sdk

echo -e "\n\tStep 5.\n"
cd ./pico-sdk
sudo git submodule update --init
cd ..

echo -e "\n\tStep 6.\n"
sudo git clone https://github.com/rsolorzanomsft/tinyusb.git
sudo rm ./pico-sdk/lib/tinyusb/src/class/hid/hid.h
sudo rm ./pico-sdk/lib/tinyusb/src/class/hid/hid_device.h 
sudo cp ./tinyusb/src/class/hid/hid.h ./pico-sdk/lib/tinyusb/src/class/hid/hid.h
sudo cp ./tinyusb/src/class/hid/hid_device.h  ./pico-sdk/lib/tinyusb/src/class/hid/hid_device.h 


echo -e "\n\tStep 7.\n"
cd ./RP2040MacropadHidSample/src/
mkdir build
cd build
cmake -DPICO_BOARD=adafruit_macropad_rp2040 ..


echo -e "\n\tStep 8.\n"
make


echo -e "\n\tThats it,\n
    9. On the Macropad, while holding down the rotary encoder button, press the reset button on the left side of the board, right under the OLED screen. Macropad device should show up as a removable device RPI-RP2 (DriveLetter:)
    10. Open an Explorer window to the build directory, and copy macropad.uf2 to the Macropad removeable device. Device should automatically remove itself and reboot.
    11. Open Settings > Personalization > Dynamic Lighting, and see the device come up.
 \n"

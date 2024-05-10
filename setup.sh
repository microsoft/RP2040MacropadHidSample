#!/bin/bash

echo -e "\n  \e[30m\e[100m                                                 \e[40m"
echo -e "  \e[100m  \e[41m  \e[42m  \e[100m    Microsoft RP2040 LampArray Sample run  \e[40m"
echo -e "  \e[100m  \e[44m  \e[43m  \e[100m    Script made by github.com/Nikpesu      \e[40m"
echo -e "  \e[100m                                                 \e[40m\e[0m"

if [ "$EUID" -ne 0 ]
  then echo -e "\n  Please run as root: sudo ./setup.sh\n"
  exit
fi

echo -e "\n\tStep 2.\n"
git clone https://github.com/microsoft/RP2040MacropadHidSample.git

echo -e "\n\tStep 3.\n"
apt install build-essential

echo -e "\n\tStep 4\n"
apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib
git clone https://github.com/raspberrypi/pico-sdk.git
rm ./RP2040MacropadHidSample/src/pico_sdk_import.cmake
cp ./pico-sdk/external/pico_sdk_import.cmake ./RP2040MacropadHidSample/src/pico_sdk_import.cmake
echo -e "path"
export PICO_SDK_PATH=$PWD/pico-sdk

echo -e "\n\tStep 5.\n"
cd ./pico-sdk
git submodule update --init
cd ..

echo -e "\n\tStep 6.\n"
git clone https://github.com/hathach/tinyusb.git
rm ./pico-sdk/lib/tinyusb/src/class/hid/hid.h
rm ./pico-sdk/lib/tinyusb/src/class/hid/hid_device.h
cp ./tinyusb/src/class/hid/hid.h ./pico-sdk/lib/tinyusb/src/class/hid/hid.h
cp ./tinyusb/src/class/hid/hid_device.h  ./pico-sdk/lib/tinyusb/src/class/hid/hid_device.h

echo -e "\n\tStep 7.\n"
cd ./RP2040MacropadHidSample/src/
rm ./build -r
mkdir build
cd build
echo -e $PICO_SDK_PATH
cmake -DPICO_BOARD=adafruit_macropad_rp2040 ..

echo -e "\n\tStep 8.\n"
make

echo -e "\n\tThats it,\n"
echo -e "  9. On the Macropad, while holding down the rotary encoder b utton, press the reset button on the left side of the board, right under the OLED screen. Macropad device should show up as a removable device RPI-RP2 (DriveLetter:)"
echo -e "  10. Open an Explorer window to the build directory, and copy macropad.uf2 to the Macropad removeable device. Device should automatically remove itself and reboot."
echo -e "  11. Open Settings > Personalization > Dynamic Lighting, and see the device come up.\n"


# Microsoft RP2040 LampArray Sample
This project includes a sample for creating a LampArray deivce on the [Adafruit Macropad](https://www.adafruit.com/product/5128), which allows it to be controlled using Windows Lighting. This is done using the [Raspberry Pi Pico C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf) and [TinyUSB](https://docs.tinyusb.org/en/latest/).

<img src="LightingDemo.gif" alt="Macropad RGB lights demo"/>

In this sample, there are two layers which are controlled by the rotary encoder. The default layer is a simple numpad layout, and the second layer is all blanks ready to be filed with any Macro command. The current design only allows one key combination to be sent at a time, and each combination is limited to two modifier keys (control, alt, shift, etc.) and 6 keys at a time, which is a limitation of the HID standard. 

This sample implements the [LampArray HID](https://www.usb.org/sites/default/files/hutrr84_-_lighting_and_illumination_page.pdf) standard, so when connected to any LampArry HID controller, this device should be able to be controlled. Additionally, a developer can control the RGB device effects from the [Windows LampArray API](https://learn.microsoft.com/en-us/uwp/api/windows.devices.lights.lamparray?view=winrt-22621). See the AutoRGB sample here: https://github.com/microsoft/Dynamic-Lighting-AutoRGB.

This can be used as a template for other RP2040 devices which are connected to NeoPixels, or the Lighting folder can be used as a starting point for any project that uses TinyUSB.

Note, this project was built off of the Hid Composite sample in the [Pico-Examples repository](https://github.com/raspberrypi/pico-examples/tree/master/usb/device/dev_hid_composite). Additionally, this project uses the PIO example in the Pico C/C++ SDK [documentation](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf?_gl=1*1sdq912*_ga*Mjk2MDU5ODkuMTY5NDQ1NjkzNg..*_ga_22FD70LWDS*MTY5NDQ1NjkzNi4xLjEuMTY5NDQ1NzAwNy4wLjAuMA..), section 3.2.2: A Real Example: WS2812 LEDs.

## Macropad Setup instructions
Note, that this project was built and tested using the latest Ubuntu WSL. Other distributions and the Windows version of the Pico SDK should work, but those options have not been verified.

1. [Install WSL](https://learn.microsoft.com/en-us/windows/wsl/install) onto Windows Machine. 
2. `git clone` this project into WSL distribtion. This directory will now be the project directory.
3. Install build dependencies.

```
sudo apt update
sudo apt install build-essential
```

4. Follow Pico SDK setup instructions from https://github.com/raspberrypi/pico-sdk up through step 2c. (For step 2, follow set up instructions by cloning the SDK) 
5. cd to the SDK directory and run `git submodule update --init`
6. Update TinyUSB in Pico SDK to latest version

```
cd <pico sdk dir>/lib/tinyusb
git checkout master
git pull
```
_Note, this may not be needed once updates to TinyUSB containing the LampArrayHID information reaches a release branch._

7. cd to `<ProjectDirectory>/src` and setup CMake build directory:
```
mkdir build
cd build
cmake -DPICO_BOARD=adafruit_macropad_rp2040 ..
```
Note, if PICO_SDK_PATH environment variable has not been set up in step 3, `-DPICO_SDK_PATH=` will need to be specified as well.

8. Make your target from the project build directory.

```
make
```

9. On the Macropad, while holding down the rotary encoder button, press the reset button on the left side of the board, right under the OLED screen. Macropad device should show up as a removable device `RPI-RP2 (DriveLetter:)`
10. Open an Explorer window to the build directory, and copy `macropad.uf2` under the build directory to the Macropad removeable device. Device should automatically remove itself and reboot.
11. Open Settings > Personalization > Dynamic Lighting, and see the device come up. 

## Contributing

This project welcomes contributions and suggestions.  Most contributions require you to agree to a
Contributor License Agreement (CLA) declaring that you have the right to, and actually do, grant us
the rights to use your contribution. For details, visit https://cla.opensource.microsoft.com.

When you submit a pull request, a CLA bot will automatically determine whether you need to provide
a CLA and decorate the PR appropriately (e.g., status check, comment). Simply follow the instructions
provided by the bot. You will only need to do this once across all repos using our CLA.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/).
For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or
contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft 
trademarks or logos is subject to and must follow 
[Microsoft's Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general).
Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship.
Any use of third-party trademarks or logos are subject to those third-party's policies.

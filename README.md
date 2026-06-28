# PaperTemp

PaperTemp is a temperature application for [Paperd.Ink](https://paperd.ink/) Classic devices. It displays the forecasted temperature for a location from OpenMeteo and the current temperature for a given [Netatmo](https://weathermap.netatmo.com/) weather station side by side.

PaperTemp is under development, it works for me but is not production ready software.

Currently, PaperTemp only supports the Paperd.Ink Classic – the Merlot hasn’t been tested (I don’t own one). If you’d like to see support added for the Merlot, feel free to open a GitHub [issue](https://github.com/cimm/papertemp/issues).

PaperTemp is made to display the temperature from Netatmo devices and OpenMeteo, but it should be straightforward to swap these with another temperature data source.

## Installation

You can use the Arduino IDE to compile and upload the sketch, but I prefer the [arduino-cli](https://arduino.github.io/arduino-cli/0.29/). First clone this git repository:

```sh
git clone https://github.com/cimm/papertemp.git --depth 1
```

Make sure to update your WiFi credentials, OpenMeteo location, and Netatmo settings in the `papertemp/config.hpp` file.

We’ll use the arduino-cli tool to compile and upload the code. If you haven’t already, follow these steps to set up the ESP32 board and install the required libraries:

```sh
arduino-cli config init
arduino-cli config set board_manager.additional_urls https://dl.espressif.com/dl/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli lib install GxEPD2@1.6.9
arduino-cli lib install ArduinoJson@7.4.3
```

Finally, compile and upload the sketch:

```sh
arduino-cli compile --fqbn esp32:esp32:esp32:PartitionScheme=no_ota
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32
```

Or compile and upload in one go:

```sh
arduino-cli compile --upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32:PartitionScheme=no_ota
```

The partition scheme may not be necessary, but it helps free space on the ESP32’s limited storage, and we don’t use OTA updates.

After uploading, the board will restart. Wait a few seconds, and if everything went well, you should see the temperature. If you get an error like ‘Could not open /dev/ttyUSB0’, you might not have permission to access the USB port. Try changing the permissions and uploading again.

```sh
sudo chmod a+rw /dev/ttyUSB0
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32
```

Use the Arduino Serial Monitor extra debug info:

```sh
arduino-cli monitor -p /dev/ttyUSB0
```

## Acknowledgement

A good chunk of the code is inspired on the official [Paperd.Ink Library for Arduino](https://github.com/paperdink/PaperdInk-Library).

## See also

I also wrote [PaperCal](https://suffix.be/blog/eink-calendar/), a similar Paperd.Ink application to display your upcoming calendar events.

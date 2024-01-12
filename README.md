<p align="center"> <img src="https://github.com/BlockThor/WS2812FX_MOODnPARTY_Edition/blob/main/WS2812FX_MnP_logo.png" align="center" width="500"/> </p>

# WS2812FX MOOD'n'PARTY - Updated, Upgraded, and Remastered

## Features

- Minimum requirement for the library: only [WS2812FX_MOODnPARTY_Edition](https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface) and [Adafruit NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel). No `SPIFFS` or `LittleFS`, no `WebSocket`, etc.
- Developed with HTML, CSS, and JavaScript. No `JQuery` or similar libraries are used, emphasizing simplicity, enhancing performance, providing customization options, reducing dependencies, and ensuring compatibility.
- Single-page interface with tabs.
- No pre-stored WiFi names and passwords required.
- No WiFi required at all - can be controlled through soft-AP mode.

## Download and Install

1. Install the [Adafruit NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel) (v1.1.7 or newer).
2. Install the [WS2812FX_MOODnPARTY_Edition library](https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface)
3. Download this repository.
4. Extract the contents into your any directory.
5. Open the Arduino IDE and open sketch `MOODnPARTY_LIGHTS.ino`.
6. Upload sketch to you ESP8266 (tested with NodeMCU v3).

## Hardware

1. WS2812b strip - ideally 60 LEDs with high density
2. ESP8266 - NodeMCU
3. Usb cable

## Software

No special software required. The lights to be controlled through web browser on you device.

## ToDo

- [ ] Change DuoMode to PaletteMode (Maybe, not sure yet).
- [ ] 

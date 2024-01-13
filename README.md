[![Stargazers][stars-shield]][stars-url] [![Forks][forks-shield]][forks-url] [![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url] [![MIT License][license-shield]][license-url] [![Instagram][instagram-shield]][instagram-url]

<p align="center"> <img src="https://github.com/BlockThor/WS2812FX_MOODnPARTY_Edition/blob/main/WS2812FX_MnP_logo.png" align="center" width="500"/> </p>

# MOOD'n'PARTY Lights - More fun with colorful lights for all!

## Interface

<p align="center"> <img src="https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface/blob/main/imgs/Interface_small.png" align="center" /> </p>

## Features

- Single-page interface with tabs.
- Developed with HTML, CSS, and JavaScript. No `JQuery` or similar libraries are used, emphasizing simplicity, enhancing performance and providing customization options.
- Minimum requirement for the library: only [WS2812FX_MOODnPARTY_Edition](https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface) and [Adafruit NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel). No `SPIFFS` or `LittleFS`, no `WebSocket`, etc.
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

- [ ] Add parameters tab to change pin, number of leds, type of leds, name and password of AP, etc.
- [ ] Light / Dark color schemes.
- [ ] Change DuoMode to PaletteMode (Maybe, not sure yet).

## PS

Tap footer on interface to find out 💎

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[stars-shield]: https://img.shields.io/github/stars/BlockThor/MOODnPARTY_LIGHTS_WebInterface?logo=github&style=flat&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[stars-url]: https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface/stargazers
[forks-shield]: https://img.shields.io/github/forks/BlockThor/MOODnPARTY_LIGHTS_WebInterface?style=flat&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[forks-url]: https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface/network/members
[contributors-shield]: https://img.shields.io/github/contributors/BlockThor/MOODnPARTY_LIGHTS_WebInterface?style=flat&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[contributors-url]: https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface/graphs/contributors
[issues-shield]: https://img.shields.io/github/issues/BlockThor/MOODnPARTY_LIGHTS_WebInterface?style=flat&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[issues-url]: https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface/issues
[license-shield]: https://img.shields.io/github/license/BlockThor/MOODnPARTY_LIGHTS_WebInterface?style=flat&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[license-url]: https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface/blob/master/LICENSE
[instagram-shield]: https://img.shields.io/badge/-Instagram-black?style=flat&logo=Instagram&logoColor=%23E6EDF3&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[instagram-url]: https://instagram.com/vasylyudin/

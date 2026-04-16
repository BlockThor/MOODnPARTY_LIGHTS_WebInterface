[![Stargazers][stars-shield]][stars-url] [![Forks][forks-shield]][forks-url] [![Contributors][contributors-shield]][contributors-url]
[![Issues][issues-shield]][issues-url] [![Code][code-shield]][code-url] [![MIT License][license-shield]][license-url] [![Instagram][instagram-shield]][instagram-url]

<p align="center"> <img src="https://github.com/BlockThor/WS2812FX_MOODnPARTY_Edition/blob/main/WS2812FX_MnP_logo.png" align="center" width="500"/> </p>

# 🟡🟣🟤 MOOD'n'PARTY Lights 🔴🟢🔵 <br> More fun with colorful lights for all!

MOOD'n'PARTY Lights is a web-based control interface for WS2812b LED strips powered by ESP8266, designed to create colorful and dynamic lighting effects for your parties or relaxing environments. Control your lights from any device with a browser -- no dependencies or WiFi credentials needed.

## Interface

### Screenshots

<p align="center"> <img src="/imgs/Interface_small.png" align="center" /> </p>

### Demo online

[CodePen](https://codepen.io/blockthor/pen/KKEaJzW)

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
4. Extract the contents into any directory.
5. Open the Arduino IDE and open sketch `MOODnPARTY_LIGHTS.ino`.
6. Upload sketch to your ESP8266 (tested with NodeMCU v3).
   
### Usage

1. After uploading, connect your device to the ESP8266’s WiFi AP.
2. Open a web browser and navigate to `1.2.3.4` to use the control interface.

## Hardware

- ESP8266 (NodeMCU recommended)
- WS2812b LED strip (e.g., 60 LEDs, vertical arrangement recommended)
- Arduino IDE

## Software

No special software required. The lights to be controlled through web browser on your device.

## ToDo

- [x] Add parameters tab to change pin, number of LEDs, type of LEDs, name and password of AP, etc.
- [x] Load time from device, Time to Switch On/Off
- [ ] Timer to switch off

- [ ] Change DuoMode to PaletteMode (Maybe, not sure yet).
- [ ] Light / Dark color schemes.
- [ ] Presets (something like Halloween, Circus Combustus, etc)
- [ ] Custom presets (set of Mode/Submode/Colors(palette)/Speed/Bri/ElementSize/FadeRate)
## PS

> [!TIP]
> Tap a footer on the interface to find out 💎

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
[code-shileld]: https://img.shields.io/github/languages/code-size/BlockThor/MOODnPARTY_LIGHTS_WebInterface?style=flat&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[code-url]: https://github.com/BlockThor//MOODnPARTY_LIGHTS_WebInterface
[license-shield]: https://img.shields.io/github/license/BlockThor/MOODnPARTY_LIGHTS_WebInterface?style=flat&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[license-url]: https://github.com/BlockThor/MOODnPARTY_LIGHTS_WebInterface/blob/master/LICENSE
[instagram-shield]: https://img.shields.io/badge/-Instagram-black?style=flat&logo=Instagram&logoColor=%23E6EDF3&labelColor=rgba(0%2C0%2C0%2C0.1)&color=rgba(0%2C0%2C0%2C0.1)
[instagram-url]: https://instagram.com/vasylyudin/


# microbit-dal-ext-kit

The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)

## Overview

The `microbit-dal-ext-kit` provides components and utilities compatible with BBC micro:bit. It also unofficially supports several extensiton boards and hardware modules. The kit consists of small C++ classes and functions, so you can use any part of them mixed with `microbit-dal` and Arm Mbed OS.

### Structure

<table>
<tr><td align="center">Application written in C++</td></tr>
<tr><td align="center"><b>microbit-dal-ext-kit</b></td></tr>
<tr><td align="center"><b>microbit-dal</b> (micro:bit runtime)</td></tr>
<tr><td align="center">Arm Mbed OS</td></tr>
<tr><td align="center" >BBC micro:bit device</td></tr>
<tr><td align="center">Extension Board and/or Hardware Module (optional)</td></tr>
<tr><td align="center">Inputs/Outputs (optional)</td></tr>
</table>

### Extension boards and hardware modules supported unofficially

+ ElecFreaks' Joystick:bit
+ Kitronik's Zip Halo
+ SparkFun's moto:bit
+ Waveshare's Mini Piano Module
+ Generic Buzzer
+ Generic NeoPixel (WS2812B) LED strip
+ Generic Sonar module (HC-SR04)

## License

MIT

## Usage Example

Yotta module | URL
------------ | ---
microbit-dal-ext-kit-example | https://github.com/softgraph/microbit-dal-ext-kit-example

## Dependencies

Yotta module | URL | Version
------------ | --- | -------
microbit     | https://github.com/lancaster-university/microbit     | v2.1.1
microbit-dal | https://github.com/lancaster-university/microbit-dal | v2.1.1

## External Resources

### Build Environment

+ [Offline development tools](https://lancaster-university.github.io/microbit-docs/offline-toolchains/)

### micro:bit runtime

+ [Introduction](https://lancaster-university.github.io/microbit-docs/)

### Arm Mbed OS

+ [BBC micro:bit](https://os.mbed.com/platforms/Microbit/)

### BBC micro:bit

+ [Micro:bit Educational Foundation](https://microbit.org)

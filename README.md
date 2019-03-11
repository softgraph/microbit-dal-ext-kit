
# microbit-dal-ext-kit

The set of components and utilities for C++ applications using `microbit-dal` (also know as micro:bit runtime)

## Overview

The `microbit-dal-ext-kit` provides components and utilities compatible with BBC micro:bit. It also unofficially supports several extensiton boards and hardware modules. The kit consists of small C++ classes and functions, so you can use any part of them mixed with `microbit-dal` and Arm Mbed OS.

### Structure

<table><tr
><td bgcolor="#ffc080" align="center" colspan="3"><font color="#000000">Application written in C++</font></td></tr><tr
><td bgcolor="#c0ffc0" align="center"><font color="#000000"><b>microbit-dal-ext-kit</b></font></td><td bgcolor="#c0c0ff"></td><td bgcolor="#ff80c0"></td></tr><tr
><td bgcolor="#c0c0ff" align="center" colspan="2"><font color="#000000"><b>microbit-dal</b> (micro:bit runtime)</font></td><td bgcolor="#ff80c0"></td></tr><tr
><td bgcolor="#ff80c0" align="center" colspan="3"><font color="#000000">Arm Mbed OS</font></td></tr><tr
><tr><td bgcolor="#ffffff" colspan="3"></td></tr><tr
><td bgcolor="#c0c0ff" align="center" colspan="3"><font color="#000000">BBC micro:bit device</font></td></tr><tr
><td bgcolor="#c0ffc0" align="center"><font color="#000000">Extension Board and/or Hardware Module (optional)</font></td><td bgcolor="#c0c0ff" colspan="2"></td></tr><tr
><td bgcolor="#ffc080" align="center" colspan="3"><font color="#000000">Inputs/Outputs (optional)</font></td></tr
></table>

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

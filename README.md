
# microbit-dal-ext-kit

The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime)

## Overview

The `microbit-dal-ext-kit` provides components and utilities compatible with BBC micro:bit. It also unofficially supports several extensiton boards and hardware modules. The kit consists of small C++ classes and functions, so you can use any part of them mixed with `microbit-dal` and Arm Mbed OS.

### Structure

<table>
<tr><td align="center"><code>microbit-dal-ext-kit-example</code> <br> (or any module written in C++)</td></tr>
<tr><td align="center"><code>microbit-dal-ext-kit</code></td></tr>
<tr><td align="center"><code>microbit</code> and <code>microbit-dal</code> <br> (also known as micro:bit runtime)</td></tr>
<tr><td align="center">Arm Mbed OS</td></tr>
<tr><td align="center">BBC micro:bit device</td></tr>
<tr><td align="center">Extension board and/or Hardware module (optional)</td></tr>
<tr><td align="center">Inputs/Outputs (optional)</td></tr>
</table>

### Module Outlines

+ `microbit-dal-ext-kit-example` <br>
	An example for using `microbit-dal-ext-kit`

+ `microbit-dal-ext-kit` <br>
	The set of components and utilities for C++ applications using `microbit-dal` (also known as micro:bit runtime) with or without `microbit`

+ `microbit-dal` <br>
	The core set of drivers, mechanisms and types that make up the micro:bit runtime.

+ `microbit` <br>
	A collection of the commonly used components of the micro:bit runtime with a standard configuration, to provide an easy to use interface for programming the micro:bit in C/C++.

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

## Resources

### Wiki

See also [the wiki page for microbit-dal-ext-kit and example](https://github.com/softgraph/microbit-dal-ext-kit-example/wiki).

### Documentation

Run [Doxygen (doxygen.nl)](http://www.doxygen.nl) with `Doxyfile` in the project root to generate the documentation.

### Usage Example

Module         | URL
-------------- | ---
`microbit-dal-ext-kit-example` | https://github.com/softgraph/microbit-dal-ext-kit-example

### Required Modules

Module         | URL | Version
-------------- | --- | -------
`microbit`     | https://github.com/lancaster-university/microbit     | v2.1.1
`microbit-dal` | https://github.com/lancaster-university/microbit-dal | v2.1.1

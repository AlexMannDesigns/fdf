# FDF

## Overview

This project serves as an introduction to graphical programming. The aim is to right a program that renders an isometric image from a matrix of numbers in a file. A library was used to spawn the window and plot individual pixels but besides that the entire program was written by myself using C.

I learned a lot about the challenges of graphical programming in the early days of computing. I also learned some interesting new mathematical concepts, as some geometry was needed to render an isometric projection.

![42.fdf](https://github.com/AlexMannDesigns/fdf/blob/main/assets/42_fdf_screenshot.png?raw=true)

## Installation

To compile this program you will need:

    - A Unix-like operating system
    - GNU Make 3.81
    - Apple clang version 15.0.0 (clang-1500.0.40.1)

This program was developed on MacOS. It has been tested on linux but it is not 'supported' - so no guarantees it will work.

You will also need everything needed to compile [MLX42](https://github.com/codam-coding-college/MLX42). System specific installation instructions can be found in the readme [here](https://github.com/codam-coding-college/MLX42?tab=readme-ov-file#installation-%EF%B8%8F).

Compile the program:

```
$ make
```

Run the program:

```
$ ./fdf [path to map]
```

You can use the option `--help` when running the program for more info.

If you have trouble getting the libraries to link, try running `brew install glfw` in the command line.

The Makefile also utilises pkg-config to find the necessary dependencies to link the glfw library. This can be very convoluted and is system dependent. Doing it this way makes the program more portable, but your computer may not have it installed. It should be there on most modern macs and linux systems but if it's not you can run `brew install pkg-config` or use whatever package manager your linux distro has (as mentioned, linux not supported so you'll have to figure it out!).

## Key events

The image can be manipulated using the following keys:

```
    - Arrow keys: Move the image
    - j, k: Adjust the slope gradients
    - -, =: Zoom out and in, respectively (= is more user-friendly than + on us keyboard layout!)
    - esc: Closes the program
```

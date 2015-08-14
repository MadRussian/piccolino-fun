Piccolino Fun
=============

This contains various mini projects that I've worked on with the [Piccolino](http://www.piccolino.rocks/)

All of these projects used Arduino IDE

# Arduino IDE

1. Go to www.piccolino.rocks and install the Arduino IDE
2. Download the libraries and put it in your arduino sketchbook/libraries directory
3. Symlink this directory so that arduino IDE sees it when you run it.
   (Ex: Linux) ln -s /path/to/piccolino-fun ~/sketchbook
4. Set the Arduino IDE board to be Arduino Pro or Pro Mini (5v, 16MHz) w/ ATMega328
5. Set the Serial Port to be /dev/ttyUSB0 or something equivalent to that

# INO
If you're not a fan of the editor on the Arduino IDE then I suggest you use 'ino'.
This allows you to use your favorite editor and then use 'ino' on the command line
to build your program.

The projects here that are designed to work with the inotool are located in ino-projects

# Install
1. Go to http://inotool.org and install it
2. Install picocom 'sudo apt-get install picocom'. This is used for monitoring the serial
2. Download the libraries from piccolino and put them in /usr/share/arduino/libraries
3. cd /usr/share/arduino/libraries; sudo mv Robot_Control .Robot_Control
   ( This is necessary because ino will try to build this and there are errors currently )

## Requirements
* src/ and lib/ directories
  * Because of this if a project is for INO then it might not show up under sketches in Arduino IDE
* picocom

## Building and Uploading

Using ino directly:

    ino build -m pro5v328
    ino upload -m pro5v328

Using ino-projects/pico-ino.py

    cd draw
    ../pico-ino.py build
    ../pico-ino.py upload

## Monitor the serial output
1. ino serial

## Making a inotool project for yourself
If you easily want to create a new project do the following:

  cd ino-projects; cp -R template PROJECT
  cd PROJECT

Then follow the building procedure.
The reason for this is that the template has an entry for the build to be ignored because
you don't want that to be included as part of a git project.


# VIM
If you're a VIM fanatic like myself then here are a couple of plugins that will colorize your sketches:
* sudar/vim-arduino-syntax
* jplaut/vim-arduino-ino.git


# FightstickOverlay

![Screenshot](https://i.imgur.com/6KGYsoN.png)

## Introduction

I made this app, intended to be used as an overlay on OBS because I didn't like any of the curent solutions.
It's quite configurable, you can change each button's position and colors according to your taste, you can also choose to show either the dpad or left stick inputs.
This app works only with Xinput controllers (so sticks like the Mayflash F500 and third party controllers should work just fine)

## Configuration

Well the configuration is straightforward, every setting is self explanatory, but do not touch the btnID setting if you don't know what you're doing. You might break the app altogether.

## How to use

FightstickOverlay loads `"Configs/default.ini"` by default, don't delete it or it'll mess up the button display. Instead, copy `default.ini`, give it another name and edit it as you wish. Once you're done just drag and drop the config file on the window.

Then you can include it in OBS as a Window capture, do not forget to use color filtering to make the black background transparent, then tweak the settings to your liking.

Do not minimize the window as it stops refreshing if you do that, leave it in the background, maybe behind the OBS window, but do not minimize it.

## Building

Sadly this app doesn't work on Linux yet because both operating systems handle controller inputs differently, even though I made a CMake configuration for Linux, and the app itself compiling correctly and launching as it should, it won't grab inputs.

You need MinGW and Raylib installed, and most importantly CMake then building it is as simple as doing these steps :

```
git clone https://github.com/Sharqo78/FightstickOverlay.git
cd FightstickOverlay
mkdir build
cd build
cmake .. -G 'Unix Makefiles'
make
```
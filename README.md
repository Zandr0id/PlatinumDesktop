# PlatinumDesktop

A simple desktop environment

This aims to be an exercise at some system building. The goal is to make a desktop environment that can create windows
for other running programs, and provide things that other desktops do like mouse and window manipulation. There
will eventually be an API library for other programs to use to connect to it like a windows server, and a GUI library
programs can use to create interface.

Currently using SDL2 as a pass-through adapter to draw to the the screen and get input events.
Eventually SDL2 should be lifted out and connections should be made to actual hardware drivers.
So make sure SDL2 is installed on your system.

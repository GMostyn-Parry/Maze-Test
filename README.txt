Author: George Mostyn-Parry
Originally created in November 2016.
Annotated and re-factored in January 2019 - February 2019.
Compiled with SFML 2.5.1, and Visual Studio 2017 in C++17.
To compile it expects SFML 2.5.1 for Visual Studio 2017 in C:\Libraries. This may be changed, simply refer to:
https://www.sfml-dev.org/tutorials/2.5/start-vc.php

A small program to generate a randomly generated maze of a passed size, using a randomised depth-first search algorithm.
The mazes do not have entry or exit points.
The size must be odd on both axes, but does not have to be uniform.

##########
EXECUTABLE
##########
There is a executable in the "Release" folder located in the root folder with a usuable executable; this contains the necessary SFML files and asset files to run.

x64 versions can be compiled but require the SFML x64 libraries to be put in C:\Libraries, or wherever the user has changed the library location to.
A debug version is also included, but has no mechanical difference to the release version.

##########
USAGE
##########

You can close the window at any time by clicking the titlebar close button on the window, or by using the 'Escape' key.

Controls
------------------------------
KEY			|	FUNCTION
------------------------------
Escape		|	Closes application.
R			|	Generate new maze of same size.
Left Arrow	|	Decreases horizontal maze size, and generates a new maze.
Right Arrow	|	Increases horizontal maze size, and generates a new maze.
Up Arrow	|	Increases vertical maze size, and generates a new maze.
Down Arrow	|	Decreases vertical maze size, and generates a new maze.
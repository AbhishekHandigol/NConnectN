# NConnectN
Two player "Connect 4" game, implemented using the NCurses library in C.

## Table of contents
* [General info](#general-info)
* [Setup](#setup)
* [Features](#features)
* [Contact](#contact)

## General info
The game works similar to the "Connect 4" strategy game, where the goal is to get 4 in a row in any direction.
Here, the user can choose the size board they want, and the number of pieces needed to win. 
The program also writes the entire board to an output file every time the cursor is pressed, which you can view after the game is over.

## Setup
* After opening the project, enter the number of rows, the number of columns, and the name of the output file you would like to write to as command line arguments.
* To move the token left, press 'a', 'j', or the left arrow key.
* To move the token right, press 's', 'k', or the right arrow key.
* To drop the token, press the spacebar or enter key.

## Features
* Using a cursor tracking window, the program can show the cursor moving around on the top of the screen, based on whether the user presses left or right.
* The size of the board and the number of pieces needed to win is customizable.

## Contact
Created by [@AbhishekHandigol](https://www.github.com/AbhishekHandigol).


# C-Backgammon-Plakoto-Game
This project was made while learning the basics of C++, it simulates of the classic Backgammon game Plakoto.

## Project Goals
The project focuses on simulating a game of Plakoto by printing a simplified board on the terminal screen. As one of my first projects, there was a lot to learn and I focused on seperating the mechanisms of the game into classes and putting them in their respective header files. Though the header connection is not managed profesionally, instead they're linked directly to the main file.

## The Layout
The program takes place entirely on 1 terminal. It starts with a message informing the user of the possible actions, them being to play (single- or multi- player), read the rules or exit. This is depicted in picture "Initial message.png".
If the player choses to exit there is no message and the program simply terminates.
If the player choses to read the rules then they are presented with the rules and the initial message replays. This is depicted in picture "Rules.png".
If the player choses to play, that's where the more complex layout presents itself.
Instead of the full 30 pawns and 24 positions there are now 14 pawns and 12 positions to both make it faster to finish a game while debugging and to make it easier to print in the screen. The rules are still the same as in the original game. 

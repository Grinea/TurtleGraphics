/*
* tools.h
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
* Provides misc tool functions to the turtlegraphics program
*/

/*Header guard*/
#ifndef TOOLS_H
#define TOOLS_H

#include "turtleGraphics.h"

/*
* strUpr
* I: line (char*)
* E: none
* P: Replacing the functionality of strupr to convert all letters to uppercase
*       in supplied string
* R: Used whenever reading and text in so that the program functions entirely
*       on upper case so there is no need for considering case comparisons
*/
void strUpr(char* line);

/*
* round
* I: numIn (double)
* E: outNum (int)
* P: Rounds the supplied double to the nearest integer, tiebreaks go to even
* R: As the line and move functions run on integers and the coords exported
*       calccoords and stored in state are doubles a rounding function was
*       required and c89 has none built in
*/
int round (double numIn);

/*
* normaliseAngle
* I: state(State*)
* E: none
* P: Normalises a supplied angle
* R: Not completely necessary but normalises the angles stored in
*       the pointer state to make log files easier to understand.
*       has no effect on the program short of protecting against 
*       integer overflow in the (highly unexpected) case of millions
*       of rotations are done in one direction
*/
void normaliseAngle(State* state);

#endif

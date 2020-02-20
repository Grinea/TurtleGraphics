/*
* tools.c
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
* Provides misc tool functions to the turtlegraphics program
*/

#include <string.h>
#include <math.h>

#include "tools.h"

/*
* strUpr
* I: line (char*)
* E: none
* P: Replacing the functionality of strupr to convert all letters to uppercase
*       in supplied string
* R: Used whenever reading and text in so that the program functions entirely
*       on upper case so there is no need for considering case comparisons
* C: I think this concept is adapted from a OOPD lecture delivered by 
*       Mark Upston
*/
void strUpr(char* line)
{
    int ii;

    for (ii = 0; ii < strlen(line); ii++)
    {
        if (line[ii] >= 'a' && line[ii] <= 'z')
        {
            line[ii] = line[ii] - ('a' - 'A');
        }
    }
}

/*
* round
* I: numIn (double)
* E: outNum (int)
* P: Rounds the supplied double to the nearest integer, tiebreaks go to even
* R: As the line and move functions run on integers and the coords exported
*       calccoords and stored in state are doubles a rounding function was
*       required and c89 has none built in
*/
int round (double numIn)
{
    int outNum; 
    int lowerLim = floor(numIn);
    int upperLim = ceil(numIn);
    double upperDiff, lowerDiff;
    
    lowerDiff = numIn - lowerLim;
    upperDiff = upperLim - numIn;

    if (lowerDiff < upperDiff)
    {
        outNum = lowerLim;
    }
    else if (upperDiff < lowerDiff)
    {
        outNum = upperLim;
    }
    /*0.5 tiebreaker*/
    else
    {
        if (lowerLim % 2 == 0)
        {
            outNum = lowerLim;
        }
        else
        {
            outNum = upperLim;
        }
    }

    return outNum;
}

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
void normaliseAngle(State* state)
{

    if (state->angle > 360)
    {
        state->angle = state->angle - (int)(state->angle / 360.0) * 360;
    }

    if (state->angle < 0.0)
    {
        state->angle = state->angle + (int)(state->angle / (-360)) * 360.0;
    }
}

/*
* tutleGraphics.h
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
* Main function file of turtle graphics
*/

/*Header guard*/
#ifndef TURTLEGRAPHICS_H
#define TURTLEGRAPHICS_H

#include <stdio.h>

/*
* Defines the struct used for storing draw commands, int respresentation of 
*       the first letter of the command (UCASE) and a double of the value of 
*       the command
*/
typedef struct
{
    int type;
    double value;
} DrawComm;

/*
* Defines the struct  used for storing the informaton about the current state  
* of the cursor (X&Y reals, angle real, pattern char, and fore and background 
* colours ints)
*/
typedef struct
{
    int fore;
    int back;
    double x;
    double y;
    double angle;
    char pattern;
} State;

/*
* processCommand
* I: state (State*), comm (DrawComm*)
* E: errCode (int)
* P: Flow control for the different commands that can be passed through the 
*       program
* R: This function is the main flow control for the processing part of the
*       program, is fed commands from main and then calls the appropriate
*       functions based on the contents of the DrawComm
*/
int processCommand(State* state, DrawComm* comm, FILE* log);

/*
* printLogging
* I: state (State*), type (Char*), newX (int), newY (int), log (FILE*)
* E: none
* P: Prints coordinates pre/post move/draw commands to log file
*       and to stderr if debug is defined at compile time
* R: Used to print various logging files by the command processor
*/
void printLogging(State* state, char* type, double newX, double newY, 
        FILE* log);

/*
* intialiseStorage
* I: state (State*)
* E: none
* P: initialise the default values of pointer state
* R: Used to set defaults to all the values for the cursor
*/
void defaultStorage(State* state);

/*
* calcCoords
* I: state(State*), distance (double), newX (double*), newY (double*)
* E: none
* P: Calculates the new x and y coordinates from the original x and y
*       coordinates and the distance and angle of movement
* R: Related to the movement and draw commands, as movements are based on
*       angles and distances and those functions work on coordinates
*/
void calcCoords(State* state, double distance, double* newX, double* newY);


/*
* plotter
* I: plotData (void*)
* E: none
* P: Prints a single character referenced in the pointer to terminal at cursor
* R: Required by the supplied function in effects.c for printing lines
*/
void plotterFunction(void* plotData);

/*
* printErr
* I: errCode (int)
* E: none
* P: Prints meaningful error message before exiting based on supplied errCode
* R: Every error code in the program relates to this table except the errCode
*       in the extraction functions, which just indiciate an error occured
*       and the errCode is replaces with the positive integer representing
*       file number by fileIOs flow control
*/
void printErr(int errCode);



#endif

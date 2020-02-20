/*
* tutleGraphics.c
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "turtleGraphics.h"
#include "effects.h"
#include "linkedList.h"
#include "fileIO.h"
#include "tools.h"

/*Defines Pi to be used in trig functions*/
#ifndef M_PI
#define M_PI (3.14159265359)
#endif

/*Defines default values for initialisaiton*/
#define DEFAULT_ANGLE (0.0)
#define DEFAULT_X (0.0)
#define DEFAULT_Y (0.0)
#define DEFAULT_FG (7)
#define DEFAULT_BG (0)
#define DEFAULT_PATTERN (43)

/*
* main
* Imports: argc (int), argv (Char* [])
* Exports: errCode (int)
* Purpose: Main function driving the turtle graphics program
* Relation to other functions: Stores the list and state and initiates
*       all further chains of functions
*/
int main(int argc, char* argv[])
{
    int errCode = 0;
    LinkedList list;
    State state;
    DrawComm* comm;
    FILE* log;

    /*Aborts if too many/few arguments supplied*/
    if (argc != 2)
    {
        errCode = -1;
    }
    else
    {
        /*Command list prep*/
        defaultStorage(&state);
        list.head = NULL;
        list.tail = NULL;
        errCode = loadCommandList(argv[1], &list);
        setFgColour(state.fore);
        setBgColour(state.back);
        if (errCode == 0)
        {
            clearScreen();
            log = fopen("graphics.log", "a");
            fprintf(log, "---\n");

            /*Command processing and incremental list node freeing*/
            while (list.head != NULL && errCode == 0)
            {
                comm = removeFirst(&list);
                errCode = processCommand(&state, comm, log);
                free(comm);
                comm = NULL;
            }
            fclose(log);
        }
        
        /*free memory incase of early exit*/
        while (list.head != NULL)
        {
            comm = removeFirst(&list);
            free(comm);        
            comm = NULL;
        }   
    }
    
    penDown();

    /*Error handling*/
    if (errCode != 0)
    {
        printErr(errCode);
    }
    
    return errCode;
}

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
int processCommand(State* state, DrawComm* comm, FILE* log)
{
    double newX, newY, distance;
    int errCode = 0;
    PlotFunc plotPtr = plotterFunction;
 
    switch (comm->type)
    {
        case 'R':
            state->angle = (state->angle + comm->value);
            normaliseAngle(state);
            break;
        case 'M':
            calcCoords(state, (comm->value), &newX, &newY);
            printLogging(state, "MOVE", newX, newY, log);
            if ((int)newX < 0 || (int)newY < 0)
            {
                errCode = -4;
            }
            else
            {
                state->x = newX;
                state->y = newY;
            }
            break;        
        case 'D':
            distance = comm->value;
            /*Part 1 fix for the wonky angles, only decement when moving on 
                cardinal directions*/
            if (fmod(state->angle, 90.0) == 0)
            {
                distance--;
            }
            calcCoords(state, distance, &newX, &newY);
            printLogging(state, "DRAW", newX, newY, log);
            if ((int)newX < 0 || (int)newY < 0)
            {
                errCode = -4;
            }
            else
            {
                line(round(state->x), round(state->y), round(newX), 
                    round(newY), plotPtr, &(state->pattern));
                
                state->x = newX;
                state->y = newY;
            }
            /*Part 2 fix for wonky angles, only move extra if decremented*/
            if (distance < comm->value)
            {
                calcCoords(state, 1, &newX, &newY);
                printLogging(state, "MOVE", newX, newY, log);
                if ((int)newX < 0 || (int)newY < 0)
                {
                    errCode = -4;
                }
                else
                {
                    state->x = newX;
                    state->y = newY;
                }
            }
            break;        
        case 'F':
            #ifndef simple
                setFgColour((int)comm->value);
                break;        
            #endif
        case 'B':
            #ifndef simple
                setBgColour((int)comm->value);
                break;        
            #endif
        case 'P':
            state->pattern = (int)comm->value;
            break;
        /*Unrecognised command made it this far, unexpected*/
        default:
            errCode = -5;
    }

    return errCode;
}

/*
* printLogging
* I: state (State*), type (Char*), newX (int), newY (int)
* E: none
* P: Prints coordinates pre/post move/draw commands to log file
*       and to stderr if debug is defined at compile time
* R:
*/
void printLogging(State* state, char* type, double newX, double newY, 
        FILE* log)
{
    char* fmtStr = "%s (%7.3f,%7.3f)-(%7.3f,%7.3f)\n";
    fprintf(log, fmtStr, type, state->x, state->y, newX, newY);
#ifdef debug
    fprintf(stderr, fmtStr, type, state->x, state->y, newX, newY);
#endif
}

/*
* intialiseStorage
* I: list (LinkedList*), state (State*)
* E: none
* P: initialise the default values of pointer state and list
* R: Used to set defaults to all the values for the cursor and list
*/
void defaultStorage(State* state)
{
    state->x = DEFAULT_X;
    state->y = DEFAULT_Y;
    state->angle = DEFAULT_ANGLE;
    state->fore = DEFAULT_FG;
    state->back = DEFAULT_BG;
    state->pattern = DEFAULT_PATTERN;
#ifdef simple
    state->fore = 0;
    state->back = 7;
#endif
}

/*
* calcCoords
* I: state(State*), distance (double), newX (double*), newY (double*)
* E: none
* P: Calculates the new x and y coordinates from the original x and y
*       coordinates and the distance and angle of movement
* R: Related to the movement and draw commands, as movements are based on
*       angles and distances and those functions work on coordinates
*/
void calcCoords(State* state, double distance, double* newX, double* newY)
{
    double toRadians = (M_PI / 180.0);

    *newX = state->x + (distance * cos(state->angle * toRadians));
    *newY = state->y - (distance * sin(state->angle * toRadians));
}


/*
* plotter
* I: plotData (void*)
* E: none
* P: Prints a single character referenced in the pointer to terminal at cursor
* R: Required by the supplied function in effects.c for printing lines
*/
void plotterFunction(void* plotData)
{
    printf("%c", *((char*)plotData));
}

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
void printErr(int errCode)
{
    switch(errCode)
    {
        case(-1):
            printf("Use ./turtleGraphics <filename>\n");
            break;
        case(-2):
            printf("File could not be loaded\n");
            break;
        case(-3):
            printf("File is empty\n");
            break;
        case(-4):
            printf("Instructions printed outside terminal area\n");
            break;
        case(-5):
            printf("Unrecognised command made it to processing stage\n");
            break;
        default:
            printf("Invalid instruction on line %d\n", errCode);
            break;
    }
}


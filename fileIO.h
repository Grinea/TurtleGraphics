/*
* fileIO.h
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
* Provides fileIO functions to the turtleGraphics program by reading text
*       files loaded with variations of 6 predefined commands and values
*       for those commands
*/

/*Header guard*/
#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"
#include "turtleGraphics.h"

/*
* loadCommadList
* I: fileName (char*), list (LinkedList*)
* E: errCode (int)
* P: Loads supplied file name and inserts the contents into the supplied 
*       LinkedList, aborts on missing file, empty file, or a command thats 
*       not expected
* R: Start point for fileIO, relies on the processLine function for all
*       flow control beyond passing errors up
*/
int loadCommandList(char* fileName, LinkedList* list);

/*
* processline
* I: line (char*), list (LinkedList*), ii (int*)
* E: errCode (int)
* P: Flow control that sends the line to the correct extraction function
*       based on first character of line and then converts extraction
*       to DrawComm and inserts to list
* R: Main flow control for the fileIO, load command list just dumbly grabs
*       and feeds lines from the file until EOF or receives an error code 
*       from this control structure
*/
int processLine(char* line, LinkedList* list, int* ii);

/*
* processDouble
* I: line (char*), expected (char*), value (double*)
* E: errCode (int)
* P: Matches the first token of string to an expected value, and then extracts
*       the second elements as a double, aborts on incorrect number of tokens 
*       or incorrect tokens (value or type)
* R: Required by the process line function for extracting a double from the
*       input string and working out what type of command to apply with it.
*/
int processDouble(char* line, char* expected, double* value);

/*
* processInt
* I: line (char*), expected (char*), value (int*)
* E: errCode (int)
* P: Matches the first token of string to an expected value, and then 
*       extracts the second elements as a int, aborts on incorrect number 
*        of tokens or incorrect tokens (value or type) A bit tricky as sscanf
*        will pick up 12 out of "12.45" when told to extract a integer so I 
*        force it to fail if it finds a . in its number token. I think 12.00
*        is still a double and therefore invalid input, even though it equals
*        the int 12.
* R: Required by the process line function for extracting an integer from
*       the line as well as the type of command to apply it to. Also protects the
*       foreground and background colour change functions by erroring out
*       if the supplied value is out of range
*/
int processInt(char* line, char* expected, int* value);

/*
* processChar
* I: line (char*), expected (char*), value (int*)
* E: errCode (int)
* P: Matches the first token of string to an expected value, and then extracts 
*    the second elements as a int, aborts on incorrect number of tokens or 
*    incorrect tokens (value or type)
* R: Required by the process line function for extracting a single character
*       for the use as the pattern
*/
int processChar(char* line, char* expected, int* value);

#endif

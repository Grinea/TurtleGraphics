/*
* FileIO.c
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
* Provides fileIO functions to the turtleGraphics program by reading text
*       files loaded with variations of 6 predefined commands and values
*       for those commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"
#include "turtleGraphics.h"
#include "fileIO.h"
#include "tools.h"

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
int loadCommandList(char* fileName, LinkedList* list)
{
    int errCode = 0, ii = 0;
    FILE* src = fopen(fileName, "r");
    char line[128];
    
    if (src == NULL)
    {
        errCode = -2;
    }
    else
    {
        if(fgets(line, 128, src) == NULL)
        {
            errCode = -3;
        }
        else
        {
            errCode = processLine(line, list, &ii);
            while(errCode == 0 && fgets(line, 128, src) != NULL)
            {
                errCode = processLine(line, list, &ii);
            }
        }
        fclose(src);
    }
    
    src = NULL;

    return errCode;
}

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
int processLine(char* line, LinkedList* list, int* ii)
{
    int errCode = 0, tempVal = 0;
    double value = 0;
    DrawComm* comm;

    strUpr(line);

    (*ii)++;

    switch (line[0])
    {
        case 'R':
            if (processDouble(line, "ROTATE", &value) == -1)
            {
                errCode = *ii;
            }
            break;
        case 'M':
            if(processDouble(line, "MOVE", &value) == -1)
            {
                errCode = *ii;
            }
            break;
        case 'D':
            if (processDouble(line, "DRAW", &value) == -1)
            {
                errCode = *ii;
            }
            break;
        case 'F':
            if (processInt(line, "FG", &tempVal) == -1)
            {
                errCode = *ii;
            }
            else
            {
                value = (double)tempVal;
            }
            break;
        case 'B':
            if (processInt(line, "BG", &tempVal) == -1)
            {
                errCode = *ii;
            }
            else
            {
                value = (double)tempVal;
            }
            break;
        case 'P':
            if (processChar(line, "PATTERN", &tempVal) == -1)
            {
                errCode = *ii;
            }
            else
            {
                value = (double)tempVal;
            }
            break;
        /*Condition for command name not being one of the expected*/
        default:
            errCode = *ii;
            break;
    }

    if (errCode == 0)
    {
        comm = (DrawComm*)malloc(sizeof(DrawComm));
        comm->type = line[0];
        comm->value = value;
        insertLast(list, comm);
    }
    
    return errCode;
}

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
int processDouble(char* line, char* expected, double* value)
{
    int errCode = 0;
    char* tok;

    tok = strtok(line, " ");
    /*Match to command name*/
    if (strcmp(tok, expected) != 0)
    {
        errCode = -1;
    }
    else
    {
        tok = strtok(NULL, " ");
        /*Ensure is not null and has double*/
        if (tok == NULL
            || sscanf(tok, "%lf", value) == EOF
            || sscanf(tok, "%lf", value) == 0)
        {
            errCode = -1;
        }
        else
        {
            tok = strtok(NULL, " ");
            /*Ensure only 2  tokens on line*/
            if (tok != NULL)
            {
                errCode = -1;
            }
        }
    }

    return errCode;
}

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
*       the line as well as the type of command to apply it to. Also protects
*       the foreground and background colour change functions by erroring out
*       if the supplied value is out of range
*/
int processInt(char* line, char* expected, int* value)
{
    int errCode = 0;
    char* tok;

    tok = strtok(line, " ");
    /*Match to command name*/
    if (strcmp(tok, expected) != 0)
    {
        errCode = -1;
    }
    else
    {
        tok = strtok(NULL, " ");
        /*Check is not null, has int, and not double*/
        if (tok == NULL
            || sscanf(tok, "%d", value) == EOF
            || sscanf(tok, "%d", value) == 0
            || strstr(tok, ".") != NULL)
        {
            errCode = -1;
        }
        else
        {
            /*Ensure BG value is in range*/
            if (strcmp(expected, "BG") == 0 && (*value < 0 || *value > 7))
            {   
                errCode = -1;
            }
            /*Ensure FG value is in range*/
            else if (strcmp(expected, "FG") == 0 
                        && (*value < 0 || *value > 15))
            {
                errCode = -1;
            }
            else
            {
                tok = strtok(NULL, " ");
                /*Ensure only 2  tokens on line*/
                if (tok != NULL)
                {
                    errCode = -1;
                }
            }
        }
    }

    return errCode;
}

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
int processChar(char* line, char* expected, int* value)
{
    int errCode = 0;
    char* tok;

    tok = strtok(line, " ");
    /*Match to command name*/
    if (strcmp(tok,expected) != 0)
    {
        errCode = -1;
    }
    else
    {
        tok = strtok(NULL, " ");
        /*Ensure is not blank and no more than 2 char (including nullterm)*/
        if (tok == NULL
                || sscanf(tok, "%c", (char*)(value)) == EOF 
                || strlen(tok) != 2)
        {
            errCode = -1;
        }
        else
        {
            tok = strtok(NULL, " ");
            /*Ensure only 2  tokens on line*/
            if (tok != NULL)
            {
                errCode = -1;
            }
        }
    }

    return errCode;
}

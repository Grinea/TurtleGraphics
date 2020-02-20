/*
* linkedList.h
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
* Provides basic linked list functionality to turtleGraphics, only contains
*       insertLast and removeFirst functionality as this is all that is
*       required by turtleGraphics
*/

/*Header guard*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

#include "turtleGraphics.h"

/*
* typedef of struct LLNode, contains a DrawComm pointer to the data and 
*       a pointer  to the next LLNode
*/
typedef struct LLNode
{
    DrawComm* comm;
    struct LLNode* next;
} LLNode;

/*
* typedef of struct LinkedList, contains a LLNode pointer each of; the node 
* representing the head, and the node representing the tail
*/
typedef struct 
{
    LLNode* head;
    LLNode* tail;
} LinkedList;

/*
* insertLast
* I: list (LinkedList*), comm (DrawComm*)
* E: none
* P: Inserts a value into a LLNode and attaches to the end of the LinkedList
*/
void insertLast(LinkedList* list, DrawComm* inComm);

/*
* removeFirst
* I: list (LinkedList*)
* E: comm (DrawComm*)
* P: Removes the first node, extracts the value and assigns it to provided 
*       pointer, frees the node memory alloc
*/
DrawComm* removeFirst(LinkedList* list);

#endif

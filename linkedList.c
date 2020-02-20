/*
* linkedList.c
* Author: Owen Frere 19520500
* Last Mod: 16/10/18
* Provides basic linked list functionality to turtleGraphics, only contains
*       insertLast and removeFirst functionality as this is all that is
*       required by turtleGraphics
*/

#include "linkedList.h"

/*
* insertLast
* I: list (LinkedList*), comm (DrawComm*)
* E: none
* P: Inserts a value into a LLNode and attaches to the end of the LinkedList
* R: This is required by the program once it has the filled linked list,
*       as it loads commands in a queue order
*/
void insertLast(LinkedList* list, DrawComm* inComm)
{
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));

    newNode->next = NULL;
    newNode->comm = inComm;

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        (*list).tail->next = newNode;
        list->tail = newNode;
    }
}

/*
* removeFirst
* I: list (LinkedList*), comm (DrawComm*)
* E: errCode (int)
* P: Removes the first node, extracts the value and assigns it to provided pointer, frees the node memory alloc
* R: This is required by the program once it has the filled linked list,
*       as it processes the order in queue order
*/
DrawComm* removeFirst(LinkedList* list)
{
    DrawComm* outComm;
    LLNode* tempNode;

    if (list->head == list->tail)
    {
        outComm = list->head->comm;
        tempNode = list->head;
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        outComm = list->head->comm;
        tempNode = list->head;
        list->head = list->head->next;
    }

    free(tempNode);
    
    return outComm;
}

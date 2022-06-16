/** @file doubly_ll.c
 *  @brief A library made for working with doubly linked
 *  list in c.
 * 
 *  This library contains various functions such as creating a
 *  list; adding, deleting, and inserting items in the list; and
 *  getting items from the list.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include "headers/doubly_ll.h"

#define throw(err) { fprintf(stderr, "%s\n", err); exit(1); }

typedef struct ErrMsgDLL {
    char *FAILED_MEMORY_ALLOCATION;
    char *INVALID_INDEX_TOO_SMALL;
    char *INVALID_INDEX_TOO_BIG;
    char *INVALID_INDEX_EQUAL;
} ErrMsgDLL;

const ErrMsgDLL DLL_ERR = {
    .FAILED_MEMORY_ALLOCATION = "Node can't be created. Memory Allocation Failed.",
    .INVALID_INDEX_TOO_SMALL = "Invalid index supplied. Index can't be a negative number.",
    .INVALID_INDEX_TOO_BIG = "Invalid index supplied. Index can't be bigger than the size of the list.",
    .INVALID_INDEX_EQUAL = "Invalid index supplied. Index can't be equal to the size of the list."
};

DoublyLinkedList createList()
{
    DoublyLinkedList list = { 0, NULL };
    return list;
}

void addToList(DoublyLinkedList *ll, void *item)
{
    insertToList(ll, ll->size, item);
}

void insertToList(DoublyLinkedList *ll, int index, void *item)
{
    if(index < 0) throw(DLL_ERR.INVALID_INDEX_TOO_SMALL);
    if(index > ll->size) throw(DLL_ERR.INVALID_INDEX_TOO_BIG);
    
    int idx;
    List *trav, temp, prev;
    
    idx = 0;
    prev = NULL;
    for(trav = &ll->list; *trav != NULL && idx != index; trav = &(*trav)->next) {
        prev = *trav;
        idx++;
    }
        
    temp = (List) malloc(sizeof(Node));
    if(temp == NULL) throw(DLL_ERR.FAILED_MEMORY_ALLOCATION);

    temp->item = item;
    temp->next = *trav;
    temp->prev = prev;
    if(*trav != NULL) {
        (*trav)->prev = temp;
    }
    *trav = temp;

    ll->size++;
}

void deleteFromList(DoublyLinkedList *ll, int index, CleanupCallback cleanupCb)
{
    if(index < 0) throw(DLL_ERR.INVALID_INDEX_TOO_SMALL);
    if(index > ll->size) throw(DLL_ERR.INVALID_INDEX_TOO_BIG);
    if(index == ll->size) throw(DLL_ERR.INVALID_INDEX_EQUAL);

    int idx;
    List *trav, temp;

    idx = 0;
    for(trav = &ll->list; *trav != NULL && idx != index; trav = &(*trav)->next) {
        idx++;
    }

    temp = *trav;
    *trav = temp->next;
    if(*trav != NULL) {
        (*trav)->prev = temp->prev;
    }

    if(cleanupCb != NULL) {
        cleanupCb(temp->item);
    }
    free(temp);

    ll->size--;
}

void clearList(DoublyLinkedList *ll, CleanupCallback cleanupCb)
{
    List *trav, temp;   
    
    for(trav = &ll->list; *trav != NULL;) {
        temp = *trav;
        trav = &(*trav)->next;

        if(cleanupCb != NULL) {
            cleanupCb(temp->item);
        }
        free(temp);
    }

    ll->list = NULL;
    ll->size = 0;
}

void *getItem(DoublyLinkedList ll, int index)
{
    if(index < 0) throw(DLL_ERR.INVALID_INDEX_TOO_SMALL);
    if(index > ll.size) throw(DLL_ERR.INVALID_INDEX_TOO_BIG);
    if(index == ll.size) throw(DLL_ERR.INVALID_INDEX_EQUAL);

    int idx;
    List trav = ll.list;
    for(idx = 1; idx < index; idx++) {
        trav = trav->next;
    }

    return trav->item;
}

int isListEmpty(DoublyLinkedList ll)
{
    return ll.size == 0 ? 1 : 0;
}
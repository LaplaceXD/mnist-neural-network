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
    cleanupCb(temp->item);
    free(temp);
}
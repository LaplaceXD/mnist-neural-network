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

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define throwMallocFailed() { fprintf(stderr, "Memory Allocation Failed."); exit(1); }
#define SHOULD_BE_NON_NEGATIVE "It should be a non-negative integer."
#define SHOULD_BE_LESS_THAN_LIST "It should not be bigger than or equal to the size of the list."
#define SHOULD_BE_LESS_THAN_OR_EQUAL_TO_LIST "It should not be bigger than the size of the list."

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
    if(index < 0) throwInvalidArgs("index", SHOULD_BE_NON_NEGATIVE);
    if(index > ll->size) throwInvalidArgs("index", SHOULD_BE_LESS_THAN_OR_EQUAL_TO_LIST);
    
    int idx;
    List *trav, temp, prev;
    
    idx = 0;
    prev = NULL;
    for(trav = &ll->list; *trav != NULL && idx != index; trav = &(*trav)->next) {
        prev = *trav;
        idx++;
    }
        
    temp = (List) malloc(sizeof(Node));
    if(temp == NULL) throwMallocFailed();

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
    if(index < 0) throwInvalidArgs("index", SHOULD_BE_NON_NEGATIVE);
    if(index >= ll->size) throwInvalidArgs("index", SHOULD_BE_LESS_THAN_LIST);

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

void *getItemByIndex(DoublyLinkedList ll, int index)
{
    if(index < 0) throwInvalidArgs("index", SHOULD_BE_NON_NEGATIVE);
    if(index >= ll.size) throwInvalidArgs("index", SHOULD_BE_LESS_THAN_LIST);

    int idx;
    List trav = ll.list;
    for(idx = 1; idx <= index; idx++) {
        trav = trav->next;
    }

    return trav->item;
}

void *travList(DoublyLinkedList *ll, TravDirection dir)
{
    void *item = NULL;
    static List list = NULL;
    static int beyondLast = 0;
    static int isFirst = 1;

    if(ll != NULL) {
        list = ll->list;
        beyondLast = 0;
        isFirst = 1;
    }

    if(list != NULL) {
        switch(dir) {
            case NEXT:
                if(list->next == NULL) {
                    beyondLast = 1;
                } else if (isFirst == 1) {
                    isFirst = 0;
                } else {
                    list = list->next;
                }

                item = beyondLast == 1 ? NULL : list->item;
                break;
            case PREV:
                if(list->prev != NULL) {
                    if(beyondLast == 1) {
                        beyondLast = 0;
                    } else {
                        list = list->prev;
                    }

                    item = list->item;
                } else {
                    isFirst = 1;
                }
                break;
            default:
                throwInvalidArgs("dir", "");
        }
    }

    return item;
}

int isListEmpty(DoublyLinkedList ll)
{
    return ll.size == 0 ? 1 : 0;
}
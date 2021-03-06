/** @file doubly_ll.h
 *  @brief Function prototypes for the doubly
 *  linked list library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the doubly linked
 *  list library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */
#pragma once

/** @brief An enum for the possible directions of navigation in a list. */
typedef enum NavDirection { NEXT, PREV } NavDirection;

/** @brief Structure for the nodes in the List */
typedef struct Node {
    void *item; 
    struct Node *prev;
    struct Node *next;
} Node, *List;

/** @brief Structure for the doubly linked list. */
typedef struct DoublyLinkedList {
    int size;
    List list;
} DoublyLinkedList;

/** @brief A callback for cleaning up the item inside of node in the list. */
typedef void (*CleanupFunc)(void *item);

/** @brief Creates a doubly linked list.
 * 
 *  @return Returns an empty list.
 */
DoublyLinkedList createList();
/** @brief Adds an item to the list.
 *  
 *  @param ll A pointer to the list.
 *  @param item A pointer to the item to
 *  be added. 
 *  @return Void.
 */
void addToList(DoublyLinkedList *ll, void *item);
/** @brief Inserts an item to the list 
 *  at a given position.
 *  
 *  @param ll A pointer to the list.
 *  @param index The index where the item is
 *  to be inserted (starts at 0).
 *  @param item A pointer to the item to
 *  be inserted. 
 *  @return Void.
 */
void insertToList(DoublyLinkedList *ll, int index, void *item);
/** @brief Deletes an item from the list
 *  at a given position.
 *  
 *  @param ll A pointer to the list.
 *  @param index The index of the item to
 *  be deleted (starts at 0).
 *  @param cleanup A callback called to cleanup
 *  the item in the list.
 *  @return Void.
 */
void deleteFromList(DoublyLinkedList *ll, int index, CleanupFunc cleanup);
/** @brief Deletes all items in a list.
 *  
 *  @param ll A pointer to the list.
 *  @param cleanup A callback called to cleanup
 *  the items in the list.
 *  @return Void.
 */
void clearList(DoublyLinkedList *ll, CleanupFunc cleanup);
/** @brief Returns an item from the list at a given
 *  index.
 *  
 *  @param ll A pointer to the list.
 *  @param index The index of the item (starts at 0).
 *  @return A pointer to the item of the list.
 */
void* getItemByIndex(DoublyLinkedList ll, int index);
/** @brief Navigates through the items of a list in order,
 *  based on a given direction, and the item in the 
 *  current position is returned.
 *  
 *  Only the first call to this function should the list
 *  be passed, since it maintains a static pointer to the
 *  contents of the list. Thus, the next calls should
 *  have a NULL value passed, if you want to get more
 *  items from the list.
 * 
 *  @example
 *  getItem(&ll, NEXT);
 *  getItem(NULL, PREV);
 *  
 *  @param ll A pointer to the list to be navigated.
 *  @param dir The direction used to navigate the list
 *  at a given step, NEXT or PREV.
 *  @return A pointer to the data contained in the 
 *  current position of the navigation, else a NULL
 *  is returned.
 */ 
void *getItem(DoublyLinkedList *ll, NavDirection dir);
/** @brief Checks if a list is empty.
 *  
 *  @param ll The list to be checked.
 *  @return 1 - If the list is empty, and 0 - If the list
 *  is not empty.
 */ 
int isListEmpty(DoublyLinkedList ll);
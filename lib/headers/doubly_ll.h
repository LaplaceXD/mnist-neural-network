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

/** @brief Structure for the nodes in the List */
typedef struct Node {
    void *item; 
    struct Node *prev;
    struct Node *next;
} Node, *List;

/** @brief */
typedef struct DoublyLinkedList {
    int size;
    List list;
} DoublyLinkedList;

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
 *  @param pos The position where the item is
 *  to be inserted.
 *  @param item A pointer to the item to
 *  be inserted. 
 *  @return Void.
 */
void insertToList(DoublyLinkedList *ll, int pos, void *item);
/** @brief Deletes an item from the list
 *  at a given position.
 *  
 *  @param ll A pointer to the list.
 *  @param pos The position of the item in the
 *  list to be deleted.
 *  @param item A pointer to the item to
 *  be inserted. 
 *  @return Void.
 */
void deleteFromList(DoublyLinkedList *ll, int pos);
/** @brief Returns an item from the list at a given
 *  position.
 *  
 *  @param ll A pointer to the list.
 *  @param pos The position of the item in the
 *  list to be deleted.
 *  @return A pointer to the item of the list.
 */
void* getItem(DoublyLinkedList ll, int pos);
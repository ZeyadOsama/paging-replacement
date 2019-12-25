//
// Created by Zeyad Osama on 12/24/19.
//

#ifndef PAGING_REPLACEMENT_LINKEDLIST_H
#define PAGING_REPLACEMENT_LINKEDLIST_H

#define TYPE int

/**
 * @brief defining linked list's node.
 */
struct Node {
    TYPE value;
    Node *next;
    int arrival_t, clockPin;

    ~Node() = default;
};

/**
 * @brief defining linked list.
 */
struct LinkedList {
    Node *head, *tail;
    int length;

    ~LinkedList() = default;
};

void initList(LinkedList *l);

void add(LinkedList *l, TYPE v);

int search(LinkedList *l, TYPE v);

void _OPTIMAL(LinkedList *l, TYPE v);

void _FIFO(LinkedList *l, TYPE v);

void _LRU(LinkedList *l, TYPE v);

void _CLOCK(LinkedList *l, TYPE v);

#endif //PAGING_REPLACEMENT_LINKEDLIST_H

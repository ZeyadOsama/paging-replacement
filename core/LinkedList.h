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

bool search(LinkedList *l, TYPE v);

void _CMD(const std::string &_policy, LinkedList *_l, const int &_pRef);

#endif //PAGING_REPLACEMENT_LINKEDLIST_H

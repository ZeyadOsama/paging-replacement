//
// Created by Zeyad Osama on 12/24/19.
//

#include <cstdlib>
#include "LinkedList.h"

int ARRIVAL_TIME = 0;
Node *clock_ptr;

Node *initNode(const int &_v) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->value = _v;
    node->next = nullptr;
    node->arrival_t = ++ARRIVAL_TIME;
    node->clockPin = 1;
    return node;
}

void initList(LinkedList *l) {
    l->head = l->tail = clock_ptr = nullptr;
    l->length = 0;
}

void add(LinkedList *l, TYPE v) {
    Node *node = initNode(v);
    l->length++;

    if (l->head == nullptr) {
        l->head = l->tail = node;
        clock_ptr = l->head;
    } else {
        l->tail->next = node;
        l->tail = node;
        clock_ptr = node->next;
        if (clock_ptr == nullptr)
            clock_ptr = l->head;
    }
}

int search(LinkedList *l, TYPE v) {
    Node *tmp = l->head;
    while (tmp != nullptr) {
        if (tmp->value == v) {
            tmp->arrival_t = ++ARRIVAL_TIME;
            tmp->clockPin = 1;
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void _OPTIMAL(LinkedList *l, TYPE v) {
    // TODO
}

void _FIFO(LinkedList *l, TYPE v) {
    static Node *node = nullptr;
    if (node == nullptr)
        node = l->head;
    else {
        if (node == l->tail)
            node = l->head;
        else
            node = node->next;
    }
    node->value = v;
}

void _LRU(LinkedList *l, TYPE v) {
    Node *tmp = l->head->next;
    Node *LRU = l->head;
    while (tmp != nullptr) {
        if (tmp->arrival_t < LRU->arrival_t)
            LRU = tmp;
        tmp = tmp->next;
    }
    LRU->value = v;
    LRU->arrival_t = ++ARRIVAL_TIME;
}

void _CLOCK(LinkedList *l, TYPE v) {
    if (clock_ptr->clockPin == 0) {
        clock_ptr->value = v;
        clock_ptr->clockPin = 1;
        clock_ptr = clock_ptr->next;
        if (clock_ptr == nullptr)
            clock_ptr = l->head;
    } else {
        Node *temp = clock_ptr->next;
        if (temp == nullptr)
            temp = l->head;
        while (temp != clock_ptr) {
            if (temp->clockPin == 0) {
                clock_ptr = temp;
                break;
            }
            temp->clockPin = 0;
            temp = temp->next;
            if (temp == nullptr)
                temp = l->head;
        }
        clock_ptr->value = v;
        clock_ptr->clockPin = 1;
        clock_ptr = clock_ptr->next;
        if (clock_ptr == nullptr)
            clock_ptr = l->head;
    }
}
//
// Created by Zeyad Osama on 12/24/19.
//

#include <cstdlib>
#include <string>
#include "LinkedList.h"

#define CMD_CNT 4

using namespace std;

int ARRIVAL_TIME = 0;
Node *clock_ptr;

void _OPTIMAL(LinkedList *l, TYPE v);

void _FIFO(LinkedList *l, TYPE v);

void _LRU(LinkedList *l, TYPE v);

void _CLOCK(LinkedList *l, TYPE v);

/**
 * @brief commands function.
 */
void (*cmd_fn[])(LinkedList *l, TYPE v) = {
        &_OPTIMAL,
        &_FIFO,
        &_LRU,
        &_CLOCK
};

/**
 * @brief commands string.
 */
string cmd_name[CMD_CNT];

void _CMD(const string &_policy, LinkedList *_l, const int &_pRef) {
    for (int i = 0; i < CMD_CNT; i++)
        if (_policy == cmd_name[i])
            return (*cmd_fn[i])(_l, _pRef);
}

void initCommands(string *cmd) {
    cmd[0] = "OPTIMAL";
    cmd[1] = "FIFO";
    cmd[2] = "LRU";
    cmd[3] = "CLOCK";
}

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
    initCommands(cmd_name);
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

bool search(LinkedList *l, TYPE v) {
    Node *tmp = l->head;
    while (tmp != nullptr) {
        if (tmp->value == v) {
            tmp->arrival_t = ++ARRIVAL_TIME;
            tmp->clockPin = 1;
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

bool searchNext(Node *n, TYPE v) {
    Node *tmp = n;
    while (tmp != nullptr) {
        if (tmp->value == v) {
            tmp->arrival_t = ++ARRIVAL_TIME;
            tmp->clockPin = 1;
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

void _OPTIMAL(LinkedList *l, TYPE v) {
    Node *tmp = l->head;
    Node *OPTIMAL = l->head;

    while (tmp != nullptr) {
        if (tmp->arrival_t > OPTIMAL->arrival_t) {
            OPTIMAL = tmp;
            break;
        }
        tmp = tmp->next;
    }
    OPTIMAL->value = v;
    OPTIMAL->arrival_t = ++ARRIVAL_TIME;
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
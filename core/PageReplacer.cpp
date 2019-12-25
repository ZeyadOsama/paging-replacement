//
// Created by Zeyad Osama on 12/24/19.
//

#include <iomanip>
#include <iostream>
#include "PageReplacer.h"
#include "LinkedList.h"

#define CMD_CNT 4

using namespace std;

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

void initCommands(string *cmd) {
    cmd[0] = "OPTIMAL";
    cmd[1] = "FIFO";
    cmd[2] = "LRU";
    cmd[3] = "CLOCK";
}

void printRow(LinkedList *l, const int _pRef, const bool &_F) {
    printf("%02d %c   ", _pRef, _F ? 'F' : ' ');
    Node *temp_ptr = l->head;
    while (temp_ptr != nullptr) {
        printf("%02d ", temp_ptr->value);
        temp_ptr = temp_ptr->next;
    }
    cout << endl;
}

PageReplacer::PageReplacer(const ReplacementPolicy &_p, const int &_cntPages) {
    policy = _p;
    cntPages = _cntPages;
    initList(&list);
    initCommands(cmd_name);
}

int PageReplacer::requestPage(const int &_pRef) {
    if (search(&list, _pRef) == 1)
        printRow(&list, _pRef, false);
    else if (list.length < cntPages) {
        add(&list, _pRef);
        printRow(&list, _pRef, false);
    } else {
        for (int i = 0; i < CMD_CNT; i++)
            if (toString(policy) == cmd_name[i]) {
                (*cmd_fn[i])(&list, _pRef);
                break;
            }
        printRow(&list, _pRef, true);
        return 1;
    }
    return 0;
}

string toString(ReplacementPolicy _p) {
    string _policy;
    if (_p == OPTIMAL)
        _policy = "OPTIMAL";
    else if (_p == FIFO)
        _policy = "FIFO";
    else if (_p == LRU)
        _policy = "LRU";
    else if (_p == CLOCK)
        _policy = "CLOCK";
    return _policy;
}

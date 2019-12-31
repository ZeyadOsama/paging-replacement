//
// Created by Zeyad Osama on 12/24/19.
//

#include <iomanip>
#include <iostream>
#include "PageReplacer.h"
#include "LinkedList.h"

using namespace std;

void printRow(const LinkedList *l, const int _pRef, const bool &_F) {
    printf("%02d %c   ", _pRef, _F ? 'F' : ' ');
    Node *temp_ptr = l->head;
    while (temp_ptr != nullptr) {
        printf("%02d ", temp_ptr->value);
        temp_ptr = temp_ptr->next;
    }
    cout << endl;
}

PageReplacer::PageReplacer(const std::string &_policy, const int &_length) {
    policy = _policy;
    length = _length;
    initList(&list);
}

int PageReplacer::requestPage(const int &_pRef) {
    if (search(&list, _pRef))
        printRow(&list, _pRef, false);
    else if (list.length < length) {
        add(&list, _pRef);
        printRow(&list, _pRef, false);
    } else {
        _CMD(policy, &list, _pRef);
        printRow(&list, _pRef, true);
        return 1;
    }
    return 0;
}

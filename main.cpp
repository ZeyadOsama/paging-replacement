///
/// main.c
/// Paging and Replacement
///
/// @author Zeyad Osama.
/// @date 2019-12-13.
/// @copyright © 2019 Zeyad Osama. All rights reserved.
///

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include "core/PageReplacer.h"
#include "core/LinkedList.h"

using namespace std;

ReplacementPolicy readReplacementPolicy(ReplacementPolicy &policy);

void readRequests(LinkedList *r);

int getPageFaults(LinkedList *requests, PageReplacer _pr);

void printHeader(const string &_policy);

void printFooter(const int &_cntPageFaults);

int main() {
    // read page count.
    int cntPages;
    cin >> cntPages;
    if (cntPages < 0)
        return EXIT_FAILURE;

    // read replacement policy.
    ReplacementPolicy policy;
    if (readReplacementPolicy(policy) == NONE)
        return EXIT_FAILURE;

    PageReplacer pr(policy, cntPages);

    LinkedList requests{};
    initList(&requests);
    readRequests(&requests);

    printHeader(toString(policy));
    int cntPageFaults = getPageFaults(&requests, pr);
    printFooter(cntPageFaults);

    return EXIT_SUCCESS;
}

ReplacementPolicy readReplacementPolicy(ReplacementPolicy &policy) {
    string r_policy;
    cin >> r_policy;
    if (r_policy == "OPTIMAL")
        policy = OPTIMAL;
    else if (r_policy == "FIFO")
        policy = FIFO;
    else if (r_policy == "LRU")
        policy = LRU;
    else if (r_policy == "CLOCK")
        policy = CLOCK;
    else
        return NONE;
    return policy;
}

void readRequests(LinkedList *r) {
    int pageRef = 0;
    while (true) {
        cin >> pageRef;
        if (pageRef == -1)
            break;
        add(r, pageRef);
    }
}

int getPageFaults(LinkedList *requests, PageReplacer _pr) {
    int cntPageFaults = 0;
    Node *temp_ptr = requests->head;
    while (temp_ptr != nullptr) {
        cntPageFaults += _pr.requestPage(temp_ptr->value);
        temp_ptr = temp_ptr->next;
    }
    return cntPageFaults;
}

void printHeader(const string &_policy) {
    cout << "Replacement Policy = " << _policy << endl;
    cout << "-------------------------------------" << endl;
    cout << "Page   Content of Frames" << endl;
    cout << "----   -----------------" << endl;
}

void printFooter(const int &_cntPageFaults) {
    cout << "-------------------------------------" << endl;
    cout << "Number of page faults = " << _cntPageFaults << endl;
}

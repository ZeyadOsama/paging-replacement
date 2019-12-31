//
// Created by Zeyad Osama on 12/24/19.
//

#ifndef PAGING_REPLACEMENT_PAGEREPLACER_H
#define PAGING_REPLACEMENT_PAGEREPLACER_H

#include "LinkedList.h"

class PageReplacer {
public:
    std::string policy;
    int length;
    LinkedList list{};

    explicit PageReplacer(const std::string &_policy, const int &_length);

    ~PageReplacer() = default;

    int requestPage(const int &_pRef);
};

#endif //PAGING_REPLACEMENT_PAGEREPLACER_H

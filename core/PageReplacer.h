//
// Created by Zeyad Osama on 12/24/19.
//

#ifndef PAGING_REPLACEMENT_PAGEREPLACER_H
#define PAGING_REPLACEMENT_PAGEREPLACER_H

#include "LinkedList.h"

enum ReplacementPolicy {
    OPTIMAL = 0,
    FIFO,
    LRU,
    CLOCK,
    NONE = -1
};

class PageReplacer {
public:
    ReplacementPolicy policy;
    int cntPages;
    LinkedList list{};

    explicit PageReplacer(const ReplacementPolicy &_p, const int &_cntPages);

    ~PageReplacer() = default;

    int requestPage(const int &_pRef);
};

std::string toString(ReplacementPolicy _p);

#endif //PAGING_REPLACEMENT_PAGEREPLACER_H

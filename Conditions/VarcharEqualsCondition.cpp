//
// Created by yantar on 15/10/23.
//

#include "VarcharEqualsCondition.h"

bool VarcharEqualsCondition::compare(varchar str) {
    int i = 0;

    while (i < VARCHAR_SIZE) {
        if (str[i] == '\0') return comparing_str[i] == '\0';

        if (str[i] != comparing_str[i]) return false;
        ++i;
    }

    return true;
}

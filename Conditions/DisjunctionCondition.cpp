//
// Created by yantar on 15/10/23.
//

#include "DisjunctionCondition.h"

bool DisjunctionCondition::is_matching(Entity* entity) {
    for (ICondition* condition: conditions) if (condition->is_matching(entity)) return true;
    return false;
}

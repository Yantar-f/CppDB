//
// Created by yantar on 15/10/23.
//

#include "ConjunctionCondition.h"

bool ConjunctionCondition::is_matching(Entity* entity) {
    for (ICondition* condition: conditions) if (! condition->is_matching(entity)) return false;
    return true;
}

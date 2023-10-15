//
// Created by yantar on 15/10/23.
//

#include "NameEqualsCondition.h"

bool NameEqualsCondition::is_matching(Entity* entity) {
    return compare(entity->name);
}

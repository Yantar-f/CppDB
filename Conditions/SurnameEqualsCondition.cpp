//
// Created by yantar on 15/10/23.
//

#include "SurnameEqualsCondition.h"

bool SurnameEqualsCondition::is_matching(Entity* entity) {
    return compare(entity->surname);
}

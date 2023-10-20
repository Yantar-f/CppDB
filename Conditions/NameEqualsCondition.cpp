//
// Created by yantar on 15/10/23.
//

#include "NameEqualsCondition.h"

NameEqualsCondition::NameEqualsCondition(std::string comparing_name) : VarcharEqualsCondition(comparing_name) {}

bool NameEqualsCondition::is_matching(Entity* entity) {
    return compare(entity->name);
}

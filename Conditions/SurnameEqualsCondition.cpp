//
// Created by yantar on 15/10/23.
//

#include "SurnameEqualsCondition.h"

SurnameEqualsCondition::SurnameEqualsCondition(std::string comparing_name) : VarcharEqualsCondition(comparing_name) {}

bool SurnameEqualsCondition::is_matching(Entity* entity) {
    return compare(entity->surname);
}

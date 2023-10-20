//
// Created by yantar on 15/10/23.
//

#include "PatronymicEqualsCondition.h"

PatronymicEqualsCondition::PatronymicEqualsCondition(std::string comparing_patronymic) : VarcharEqualsCondition(comparing_patronymic) {}

bool PatronymicEqualsCondition::is_matching(Entity* entity) {
    return compare(entity->patronymic);
}

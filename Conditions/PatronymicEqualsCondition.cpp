//
// Created by yantar on 15/10/23.
//

#include "PatronymicEqualsCondition.h"

bool PatronymicEqualsCondition::is_matching(Entity* entity) {
    return compare(entity->patronymic);
}

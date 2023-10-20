//
// Created by yantar on 20/10/23.
//

#include "KeyEqualsCondition.h"

KeyEqualsCondition::KeyEqualsCondition(long comparing_key) : comparing_key(comparing_key) {}

bool KeyEqualsCondition::is_matching(Entity* entity) {
    return comparing_key == entity->key;
}

//
// Created by yantar on 20/10/23.
//

#include "TimestampEqualsCondition.h"

TimestampEqualsCondition::TimestampEqualsCondition(long comparing_timestamp) : comparing_timestamp(comparing_timestamp) {}

bool TimestampEqualsCondition::is_matching(Entity* entity) {
    return comparing_timestamp == entity->timestamp;
}

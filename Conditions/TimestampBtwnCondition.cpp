//
// Created by yantar on 20/10/23.
//

#include "TimestampBtwnCondition.h"

TimestampBtwnCondition::TimestampBtwnCondition(long start, long end) : start(start), end(end) {}

bool TimestampBtwnCondition::is_matching(Entity* entity) {
    return start < entity->timestamp && end > entity->timestamp;
}

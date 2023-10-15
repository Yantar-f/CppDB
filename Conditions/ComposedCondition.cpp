//
// Created by yantar on 15/10/23.
//

#include "ComposedCondition.h"

ComposedCondition::~ComposedCondition() {
    for (ICondition* condition: conditions) delete condition;
}

void ComposedCondition::add(ICondition* condition) {
    conditions.push_back(condition);
}


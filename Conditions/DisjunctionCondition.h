//
// Created by yantar on 15/10/23.
//

#ifndef OSLAB2_DISJUNCTIONCONDITION_H
#define OSLAB2_DISJUNCTIONCONDITION_H


#include "ComposedCondition.h"

class DisjunctionCondition : public ComposedCondition{
    DisjunctionCondition() {}

    bool is_matching(Entity* entity) override;
};


#endif //OSLAB2_DISJUNCTIONCONDITION_H

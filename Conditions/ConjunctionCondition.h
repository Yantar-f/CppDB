//
// Created by yantar on 15/10/23.
//

#ifndef OSLAB2_CONJUNCTIONCONDITION_H
#define OSLAB2_CONJUNCTIONCONDITION_H


#include <vector>
#include "ICondition.h"
#include "ComposedCondition.h"

class ConjunctionCondition : public ComposedCondition{

public:
    ConjunctionCondition() {}

    bool is_matching(Entity* entity) override;

};


#endif //OSLAB2_CONJUNCTIONCONDITION_H

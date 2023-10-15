//
// Created by yantar on 15/10/23.
//

#ifndef OSLAB2_COMPOSEDCONDITION_H
#define OSLAB2_COMPOSEDCONDITION_H


#include <vector>
#include "ICondition.h"

class ComposedCondition : public ICondition {
protected:
    std::vector<ICondition*> conditions;
public:
    ~ComposedCondition();
    void add(ICondition* condition);
};


#endif //OSLAB2_COMPOSEDCONDITION_H

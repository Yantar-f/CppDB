//
// Created by yantar on 09/10/23.
//

#ifndef OSLAB2_ICONDITION_H
#define OSLAB2_ICONDITION_H

#include "../Entity.h"

class ICondition {
public:
    virtual ~ICondition() {}
    virtual bool is_matching(Entity* entity) = 0;
};

#endif //OSLAB2_ICONDITION_H

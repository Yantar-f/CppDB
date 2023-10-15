//
// Created by yantar on 15/10/23.
//

#ifndef DBLAB_NAMEEQUALSCONDITION_H
#define DBLAB_NAMEEQUALSCONDITION_H


#include "VarcharEqualsCondition.h"

class NameEqualsCondition : public VarcharEqualsCondition {
public:
    bool is_matching(Entity* entity) override;
};


#endif //DBLAB_NAMEEQUALSCONDITION_H

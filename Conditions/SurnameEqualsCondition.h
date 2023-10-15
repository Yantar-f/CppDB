//
// Created by yantar on 15/10/23.
//

#ifndef DBLAB_SURNAMEEQUALSCONDITION_H
#define DBLAB_SURNAMEEQUALSCONDITION_H


#include "VarcharEqualsCondition.h"

class SurnameEqualsCondition : public VarcharEqualsCondition {
public:
    bool is_matching(Entity* entity) override;
};


#endif //DBLAB_SURNAMEEQUALSCONDITION_H

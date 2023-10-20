//
// Created by yantar on 15/10/23.
//

#ifndef DBLAB_NAMEEQUALSCONDITION_H
#define DBLAB_NAMEEQUALSCONDITION_H


#include "VarcharEqualsCondition.h"

class NameEqualsCondition : public VarcharEqualsCondition {
public:
    NameEqualsCondition(std::string comparing_name);
    bool is_matching(Entity* entity) override;
};


#endif //DBLAB_NAMEEQUALSCONDITION_H

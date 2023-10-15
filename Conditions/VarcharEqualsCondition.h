//
// Created by yantar on 15/10/23.
//

#ifndef OSLAB2_NAMEEQUALSCONDITION_H
#define OSLAB2_NAMEEQUALSCONDITION_H


#include "ICondition.h"

class VarcharEqualsCondition : ICondition{
std::string comparing_str;
protected:
    bool compare(varchar str);
};


#endif //OSLAB2_NAMEEQUALSCONDITION_H

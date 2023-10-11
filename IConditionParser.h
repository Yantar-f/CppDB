//
// Created by yantar on 11/10/23.
//

#ifndef OSLAB2_ICONDITIONPARSER_H
#define OSLAB2_ICONDITIONPARSER_H


#include <string>
#include "ICondition.h"

class IConditionParser {
public:
    virtual ICondition parse(const std::string& condition_statement) = 0;
};


#endif //OSLAB2_ICONDITIONPARSER_H

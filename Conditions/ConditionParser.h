//
// Created by yantar on 11/10/23.
//

#ifndef OSLAB2_CONDITIONPARSER_H
#define OSLAB2_CONDITIONPARSER_H


#include "IConditionParser.h"

class ConditionParser : public IConditionParser{
public:
    ICondition* parse(const std::string& condition_statement) override;
};


#endif //OSLAB2_CONDITIONPARSER_H

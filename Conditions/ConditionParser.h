//
// Created by yantar on 11/10/23.
//

#include "IConditionParser.h"
#include "../Logger.h"

#ifndef OSLAB2_CONDITIONPARSER_H
#define OSLAB2_CONDITIONPARSER_H

class ConditionParser : public IConditionParser {
    Logger logger {"ConditionParser"};
public:
    ICondition* parse(const std::string& condition_statement) override;
};


#endif //OSLAB2_CONDITIONPARSER_H

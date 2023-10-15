//
// Created by yantar on 10/10/23.
//

#ifndef OSLAB2_ICOMMANDHANDLER_H
#define OSLAB2_ICOMMANDHANDLER_H


#include <string>
#include "Conditions/IConditionParser.h"

class ICommandHandler {
public:
    virtual bool handle(const std::string& command) = 0;
};


#endif //OSLAB2_ICOMMANDHANDLER_H

//
// Created by yantar on 10/10/23.
//

#ifndef OSLAB2_COMMANDHANDLER_H
#define OSLAB2_COMMANDHANDLER_H

#include <map>
#include "ICommandHandler.h"
#include "Logger.h"
#include "Repository.h"

class CommandHandler : public ICommandHandler {
private:
    static const std::map <std::string, char> command_mapping;
    IConditionParser& condition_parser;
    Repository& repository;
    Logger logger {"CommandHandler"};
public:
    CommandHandler(Repository& repository, IConditionParser& condition_parser);
    bool handle(const std::string& command) override;
};


#endif //OSLAB2_COMMANDHANDLER_H

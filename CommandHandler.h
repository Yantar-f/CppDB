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
    static const std::map <std::string, int> command_mapping;
    Repository repository;
    Logger logger {"CommandHandler"};
public:
    CommandHandler(Repository& repository);
    bool handle(std::string& command);
};


#endif //OSLAB2_COMMANDHANDLER_H

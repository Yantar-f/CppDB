//
// Created by yantar on 10/10/23.
//

#ifndef OSLAB2_COMMANDHANDLER_H
#define OSLAB2_COMMANDHANDLER_H

#include "ICommandHandler.h"
#include "Logger.h"
#include "Repository.h"

class CommandHandler : public ICommandHandler {
private:
    IConditionParser& condition_parser;
    Repository& repository;
    Logger logger {"CommandHandler"};
public:
    CommandHandler(Repository& repository, IConditionParser& condition_parser);
    bool handle(const std::string& command) override;
private:
    bool selectOp(std::stringstream& stream, std::string& buf);
    bool deleteOp(std::stringstream& stream, std::string& buf);
    bool updateOp(std::stringstream& stream, std::string& buf);
    bool insertOp(std::stringstream& stream, std::string& buf);
};


#endif //OSLAB2_COMMANDHANDLER_H

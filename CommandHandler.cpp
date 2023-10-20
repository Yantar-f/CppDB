//
// Created by yantar on 10/10/23.
//

#include <sstream>
#include <iostream>
#include "CommandHandler.h"
#include "Entity.h"

#define COMMAND_MAX_LENGTH (150)
#define SELECT_STATEMENT ("SELECT")
#define DELETE_STATEMENT ("DELETE")
#define INSERT_STATEMENT ("INSERT")
#define UPDATE_STATEMENT ("UPDATE")
#define EXIT_STATEMENT ("EXIT")
#define CONDITION_DECLARATION ("WHERE")

void declare_output() {
    std::cout << "[\033[1;92mOUTPUT\033[0m] ---> {";
}

void end_output() {
    std::cout << "}\n";
}

void show_entities(std::vector<Entity*>& entities) {
    declare_output();
    std::cout << std::endl;
    for (Entity* entity : entities) std::cout << "\t" << *entity << std::endl;
    end_output();
}


CommandHandler::CommandHandler(Repository& repository, IConditionParser& condition_parser) :
    repository(repository),
    condition_parser(condition_parser) {}


bool CommandHandler::handle(const std::string& command) {
    if (command.size() > COMMAND_MAX_LENGTH) {
        logger.log_error("command too large");
        return true;
    }

    std::stringstream stream {command};
    std::string buf;

    if ( ! (stream >> buf)) {
        logger.log_error("invalid command");
        return true;
    }

    if (buf == SELECT_STATEMENT) {return selectOp(stream, buf);}
    else if (buf == DELETE_STATEMENT) {return deleteOp(stream, buf);}
    else if (buf == INSERT_STATEMENT) {return insertOp(stream, buf);}
    else if (buf == UPDATE_STATEMENT) {return updateOp(stream, buf);}
    else if (buf == EXIT_STATEMENT) {return false;}
    else {logger.log_error("invalid command");}

    return true;
}


bool CommandHandler::selectOp(std::stringstream& stream, std::string& buf) {
    if (!(stream >> buf)) {
        std::vector<Entity*> entities = repository.select_all();
        if (!entities.empty()) show_entities(entities);
    } else {
        if (buf != CONDITION_DECLARATION) {
            logger.log_error("invalid command");
            return true;
        }

        std::string condition_str;
        ICondition* condition;
        std::getline(stream, condition_str);

        try {
            condition = condition_parser.parse(condition_str);
        } catch (std::invalid_argument ex) {
            logger.log_error("invalid command");
            return true;
        }

        std::vector<Entity*> entities = repository.select(*condition);

        if (!entities.empty()) show_entities(entities);

        delete condition;
    }

    return true;
}

bool CommandHandler::deleteOp(std::stringstream& stream, std::string& buf) {
    if (!(stream >> buf)) {
        repository.remove_all();
    } else {
        if (buf != CONDITION_DECLARATION) {
            logger.log_error("invalid command");
            return true;
        }

        std::string condition_str;
        ICondition* condition;
        std::getline(stream, condition_str);

        try {
            condition = condition_parser.parse(condition_str);
        } catch (std::invalid_argument ex) {
            logger.log_error("invalid command");
            return true;
        }

        repository.remove(*condition);
        delete condition;
    }

    return true;
}

bool CommandHandler::updateOp(std::stringstream& stream, std::string& buf) {
    if (stream.eof()) {
        logger.log_error("invalid command");
        return true;
    }

    Entity updating_entity;

    try {
        stream >> updating_entity;
    } catch (std::invalid_argument ex) {
        logger.log_error("invalid command: ");
        return true;
    }

    if (!(stream >> buf) || buf != CONDITION_DECLARATION) {
        logger.log_error("invalid command");
        return true;
    }

    std::string condition_str;
    ICondition* condition;
    std::getline(stream, condition_str);

    try {
        condition = condition_parser.parse(condition_str);
    } catch (std::invalid_argument ex) {
        logger.log_error("invalid command: ");
        return true;
    }

    repository.update(updating_entity, *condition);

    delete condition;
    return true;
}

bool CommandHandler::insertOp(std::stringstream& stream, std::string& buf) {
    if (stream.eof()) {
        logger.log_error("invalid command");
        return true;
    }

    Entity new_entity;

    try {
        stream >> new_entity;
    } catch (std::invalid_argument ex) {
        logger.log_error("invalid command");
        return true;
    }

    repository.insert(new_entity);

    return true;
}


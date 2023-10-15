//
// Created by yantar on 10/10/23.
//

#include <sstream>
#include <iostream>
#include <limits>
#include "CommandHandler.h"
#include "Entity.h"

#define COMMAND_MAX_LENGTH (150)
#define SELECT_STATEMENT ("SELECT")
#define SELECT_STATEMENT_CODE (1)
#define DELETE_STATEMENT ("DELETE")
#define DELETE_STATEMENT_CODE (2)
#define INSERT_STATEMENT ("INSERT")
#define INSERT_STATEMENT_CODE (3)
#define UPDATE_STATEMENT ("UPDATE")
#define UPDATE_STATEMENT_CODE (4)
#define EXIT_STATEMENT ("EXIT")
#define EXIT_STATEMENT_CODE (5)
#define CONDITION_DECLARATION ("WHERE")

constexpr auto stream_max_size = std::numeric_limits<std::streamsize>::max();

const std::map<std::string, char> CommandHandler::command_mapping {
    {SELECT_STATEMENT, SELECT_STATEMENT_CODE},
    {DELETE_STATEMENT, DELETE_STATEMENT_CODE},
    {INSERT_STATEMENT, INSERT_STATEMENT_CODE},
    {UPDATE_STATEMENT, UPDATE_STATEMENT_CODE},
    {EXIT_STATEMENT, EXIT_STATEMENT_CODE}
};

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

    int command_code;

    try {
        command_code = command_mapping.at(buf);
    } catch (std::out_of_range ex) {
        logger.log_error("invalid command");
        return true;
    }

    switch (command_code) {
        case SELECT_STATEMENT_CODE: {
            if (!(stream >> buf)) {
                std::vector<Entity*> entities = repository.select_all();

                if (!entities.empty()) show_entities(entities);
            } else {
                if (buf != CONDITION_DECLARATION) {
                    logger.log_error("invalid command");
                    return true;
                }

                std::string condition_str;
                std::getline(stream, condition_str);

                ICondition* condition = condition_parser.parse(condition_str);
                std::vector<Entity*> entities = repository.select(*condition);

                if (!entities.empty()) show_entities(entities);
            }
            break;
        } case DELETE_STATEMENT_CODE: {
            if (!(stream >> buf)) {
                repository.remove_all();
            } else {
                if (buf != CONDITION_DECLARATION) {
                    logger.log_error("invalid command");
                    return true;
                }

                std::string condition_str;
                std::getline(stream, condition_str);

                ICondition* condition = condition_parser.parse(condition_str);

                repository.remove(*condition);

                delete condition;
            }
            break;
        } case INSERT_STATEMENT_CODE: {
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
            break;
        } case UPDATE_STATEMENT_CODE: {
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

            stream.ignore(stream_max_size, ')');

            if (!(stream >> buf) || buf != CONDITION_DECLARATION) {
                logger.log_error(buf.c_str());
                logger.log_error("invalid command");
                return true;
            }

            /*
            std::string condition_str;
            std::getline(stream, condition_str);

            ICondition* condition = condition_parser.parse(condition_str);

            repository.update(updating_entity, *condition);*/

            break;
        } case EXIT_STATEMENT_CODE:
            return false;
        default:
            logger.log_error("invalid command");
    }

    return true;
}

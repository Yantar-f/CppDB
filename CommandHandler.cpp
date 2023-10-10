//
// Created by yantar on 10/10/23.
//

#include <sstream>
#include <iostream>
#include "CommandHandler.h"

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

const std::map<std::string, int> CommandHandler::command_mapping {
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


CommandHandler::CommandHandler(Repository& repository) : repository(repository) {}

bool CommandHandler::handle(std::string& command) {
    std::stringstream stream{command};
    std::string buf;

    if (!(stream >> buf)) {
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
        case SELECT_STATEMENT_CODE:
            if (!(stream >> buf)) {
                std::vector<Entity*> entities = repository.get_all();
                declare_output();

                if (entities.empty()) {
                    std::cout << "\n\tno entities" << std::endl;
                } else {
                    std::cout << std::endl;
                    for (Entity* entity : entities) {
                        std::cout << "\tentity {" << "key = " << entity->key
                            << ", name = " << entity->name
                            << ", surname = " << entity->surname
                            << ", patronymic = " << entity->patronymic
                            << ", timestamp = " << entity->timestamp
                            << "}\n";
                    }
                }
                end_output();
                return true;
            } else {

            }
            break;
        case DELETE_STATEMENT_CODE:
            break;
        case INSERT_STATEMENT_CODE:

            break;
        case UPDATE_STATEMENT_CODE:
            break;
        case EXIT_STATEMENT_CODE:
            return false;
        default:
            logger.log_error("invalid command");
            return true;
    }

    return true;
}

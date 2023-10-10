//
// Created by yantar on 10/10/23.
//

#include <sstream>
#include "CommandHandler.h"

#define SELECT_STATEMENT ("SELECT")
#define SELECT_STATEMENT_CODE (1)
#define DELETE_STATEMENT ("DELETE")
#define DELETE_STATEMENT_CODE (2)
#define SAVE_STATEMENT ("SAVE")
#define SAVE_STATEMENT_CODE (3)
#define UPDATE_STATEMENT ("UPDATE")
#define UPDATE_STATEMENT_CODE (4)
#define EXIT_STATEMENT ("EXIT")
#define EXIT_STATEMENT_CODE (5)

const std::map<std::string, int> CommandHandler::command_mapping {
    {SELECT_STATEMENT, SELECT_STATEMENT_CODE},
    {DELETE_STATEMENT, DELETE_STATEMENT_CODE},
    {SAVE_STATEMENT, SAVE_STATEMENT_CODE},
    {UPDATE_STATEMENT, UPDATE_STATEMENT_CODE},
    {EXIT_STATEMENT, EXIT_STATEMENT_CODE}
};

CommandHandler::CommandHandler(Repository& repository) : repository(repository) {}

bool CommandHandler::handle(std::string &command) {
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
            break;
        case DELETE_STATEMENT_CODE:
            break;
        case SAVE_STATEMENT_CODE:
            break;
        case UPDATE_STATEMENT_CODE:
            break;
        case EXIT_STATEMENT_CODE:
            return false;
    }

    return true;
}

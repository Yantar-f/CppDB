#include <iostream>
#include "Logger.h"
#include "Repository.h"
#include "CommandHandler.h"
#include "ConditionParser.h"

#define FILE_NAME ("file1")

void declare_input() {
    std::cout << "[\033[1;92mINPUT\033[0m] ---> ";
}

int main() {
    Logger logger("main");
    logger.log_info("application started");

    Repository repository {FILE_NAME};
    ConditionParser condition_parser;
    CommandHandler command_handler {repository, condition_parser};
    std::string input;

    logger.log_info("ready to accept commands");

    while (true) {
        declare_input();
        std::getline(std::cin, input);
        if ( ! command_handler.handle(input)) break;
    }

    logger.log_info("application finished");
    return 0;
}

//
// Created by yantar on 09/10/23.
//

#include <iostream>
#include <ctime>
#include "Logger.h"

Logger::Logger(const char* actor_name) :
        actor_name(actor_name),
        info_prefix(std::string("[\033[1;96mINFO\033[0m]:[\033[95m").append(actor_name).append("\033[0m]:")),
        warn_prefix(std::string("[\033[1;93mWARN\033[0m]:[\033[95m").append(actor_name).append("\033[0m]:")),
        error_prefix(std::string("[\033[1;31mERROR\033[0m]:[\033[95m").append(actor_name).append("\033[0m]:")),
        fatal_prefix(std::string("[\033[1;91mFATAL\033[0m]:[\033[95m").append(actor_name).append("\033[0m]:")){}

void Logger::log_info(const char *message) {
    print(info_prefix, message);
}

void Logger::log_warn(const char* message) {
    print(warn_prefix, message);
}

void Logger::log_error(const char* message) {
    print(error_prefix, message);
}

void Logger::log_fatal(const char* message) {
    print(fatal_prefix, message);
}

void Logger::print(std::string &log_prefix, const char* message) {
    time_t now = time(nullptr);
    tm* gmt = gmtime(&now);

    std::cout << log_prefix << "["
        << 1900 + gmt->tm_year << "-"
        << gmt->tm_mon << "-"
        << gmt->tm_mday << "T"
        << gmt->tm_hour << ":"
        << gmt->tm_min << ":"
        << gmt->tm_sec
        << gmt->tm_zone
        << "] ---> " << message << std::endl;
}

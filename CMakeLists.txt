cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        OSLab2
        main.cpp
        Logger.h
        Logger.cpp
        Logger.h
        Entity.h Repository.h ICondition.h Repository.cpp ICommandHandler.h CommandHandler.cpp CommandHandler.h)

cmake_minimum_required(VERSION 3.24)
project(DBLab)
set(CMAKE_CXX_STANDARD 17)
add_executable(
        OSLab2
        main.cpp
        Logger.h
        Logger.cpp
        Logger.h
        Entity.h
        Repository.h
        Repository.cpp
        ICommandHandler.h
        CommandHandler.cpp
        CommandHandler.h
        Entity.cpp
        Conditions/ICondition.h
        Conditions/IConditionParser.h
        Conditions/ConditionParser.cpp
        Conditions/ConditionParser.h
        Conditions/VarcharEqualsCondition.cpp
        Conditions/VarcharEqualsCondition.h
        Conditions/NameEqualsCondition.cpp
        Conditions/NameEqualsCondition.h
        Conditions/SurnameEqualsCondition.cpp
        Conditions/SurnameEqualsCondition.h
        Conditions/PatronymicEqualsCondition.cpp
        Conditions/PatronymicEqualsCondition.h
        Conditions/TimestampEqualsCondition.cpp Conditions/TimestampEqualsCondition.h Conditions/KeyEqualsCondition.cpp Conditions/KeyEqualsCondition.h Conditions/TimestampBtwnCondition.cpp Conditions/TimestampBtwnCondition.h)

//
// Created by yantar on 11/10/23.
//

#include <sstream>
#include "ConditionParser.h"
#include "NameEqualsCondition.h"
#include "SurnameEqualsCondition.h"
#include "PatronymicEqualsCondition.h"
#include "TimestampEqualsCondition.h"
#include "KeyEqualsCondition.h"
#include "TimestampBtwnCondition.h"

#define EQUALS_DEF ("=")
#define BETWEEN_DEF ("BTWN")
#define KEY_FIELD ("key")
#define NAME_FIELD ("name")
#define SURNAME_FIELD ("surname")
#define PATRONYMIC_FIELD ("patronymic")
#define TIMESTAMP_FIELD ("timestamp")

ICondition* ConditionParser::parse(const std::string &condition_statement) {
    std::stringstream stream {condition_statement};
    std::string field, operand;

    if (! (stream >> field)) {
        logger.log_error("invalid condition");
        throw std::invalid_argument("invalid condition");
    }

    if (! (stream >> operand)) {
        logger.log_error("invalid condition");
        throw std::invalid_argument("invalid condition");
    }

    if (stream.get() != ' ') {
        logger.log_error("invalid condition");
        throw std::invalid_argument("invalid condition");
    }

    char c;

    if (operand == EQUALS_DEF) {
        do {c = stream.get();} while (c == ' ');

        if (c == -1 ) {
            logger.log_error("invalid condition");
            throw std::invalid_argument("invalid condition");
        }


        if (c == '"') {
            if (field == TIMESTAMP_FIELD || field == KEY_FIELD) {
                logger.log_error("invalid condition");
                throw std::invalid_argument("invalid condition");
            }

            std::string value;
            c = stream.get();

            while (c != '"') {
                if (c == -1) {
                    logger.log_error("invalid condition");
                    throw std::invalid_argument("invalid condition");
                }
                value.push_back(c);
                c = stream.get();
            }

            if (field == NAME_FIELD) {
                return new NameEqualsCondition(value);
            } else if (field == SURNAME_FIELD) {
                return new SurnameEqualsCondition(value);
            } else if (field == PATRONYMIC_FIELD) {
                return new PatronymicEqualsCondition(value);
            } else {
                logger.log_error("invalid condition");
                throw std::invalid_argument("invalid condition");
            }


        } else {
            if (field != TIMESTAMP_FIELD && field != KEY_FIELD) {
                logger.log_error("invalid condition");
                throw std::invalid_argument("invalid condition");
            }

            int value = 0;

            if (c < 49 || c > 57) {
                logger.log_error("invalid condition");
                throw std::invalid_argument("invalid condition");
            }

            value += c - 48;
            c = stream.get();

            while (c != -1 && c != ' ') {
                if (c < 48 || c > 57) {
                    logger.log_error("invalid condition");
                    throw std::invalid_argument("invalid condition");
                }
                value *= 10;
                value += c - 48;
                c = stream.get();
            }

            if (field == TIMESTAMP_FIELD) {
                return new TimestampEqualsCondition(value);
            }

            return new KeyEqualsCondition(value);
        }
    } else if (operand == BETWEEN_DEF) {
        if (field != TIMESTAMP_FIELD) {
            logger.log_error("invalid condition: invalid operand");
            throw std::invalid_argument("invalid condition");
        }

        c = stream.get();

        while (c == ' ') c = stream.get();

        if (c != '(') {
            logger.log_error("invalid condition");
            throw std::invalid_argument("invalid condition");
        }

        int start = 0, end = 0;

        c = stream.get();

        if (c < 49 || c > 57) {
            logger.log_error("invalid condition");
            throw std::invalid_argument("invalid condition");
        }

        start += c - 48;
        c = stream.get();

        while (c != ' ' && c!= ',') {
            if (c < 48 || c > 57) {
                logger.log_error("invalid condition");
                throw std::invalid_argument("invalid condition");
            }
            start *= 10;
            start += c - 48;
            c = stream.get();
        }

        while (c == ' ') c = stream.get();

        if (c != ',') {
            logger.log_error("invalid condition ,");
            throw std::invalid_argument("invalid condition");
        }

        do {c = stream.get();} while (c == ' ');

        if (c < 49 || c > 57) {
            logger.log_error("invalid condition");
            throw std::invalid_argument("invalid condition");
        }

        end += c - 48;
        c = stream.get();

        while (c != ' ' && c!= ')') {
            if (c < 48 || c > 57) {
                logger.log_error("invalid condition");
                throw std::invalid_argument("invalid condition");
            }
            end *= 10;
            end += c - 48;
            c = stream.get();
        }

        if (c == ' ') do {c = stream.get();} while (c == ' ');

        if (c != ')') {
            logger.log_error("invalid condition");
            throw std::invalid_argument("invalid condition");
        }

        return new TimestampBtwnCondition(start, end);
    } else {
        logger.log_error("invalid condition: invalid operand");
        throw std::invalid_argument("invalid condition");
    }
}

//
// Created by yantar on 09/10/23.
//

#ifndef OSLAB2_ENTITY_H
#define OSLAB2_ENTITY_H

#include <iostream>
#include <algorithm>

#define VARCHAR_SIZE (255)
#define VARCHAR_CAPACITY (VARCHAR_SIZE + 1)

typedef char varchar[VARCHAR_CAPACITY];



class Entity {
public:
    int key {0};
    varchar name;
    varchar surname;
    varchar patronymic;
    long timestamp {0};

    Entity(const char* name, const char* surname, const char* patronymic, long timestamp);
    Entity();

    friend std::ostream& operator<<(std::ostream& os, const Entity& entity) {
        os << "entity {" << "key = " << entity.key
           << ", name = " << entity.name
           << ", surname = " << entity.surname
           << ", patronymic = " << entity.patronymic
           << ", timestamp = " << entity.timestamp
           << "}";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Entity& entity) {
        std::string input;
        std::getline(is, input);

        int i = 0, j = 0;

        while (input[++i] == ' ') {}
        if (input[i] == '\0') throw std::invalid_argument("invalid input: end of line");

        if (input[i] != '(') throw std::invalid_argument("invalid input: opening fail");

        while (input[++i] == ' ') {}
        if (input[i] == '\0') throw std::invalid_argument("invalid input: end of line");

        while (input[i] != ',') {
            if (input[i] == '\0' || j == VARCHAR_CAPACITY) throw std::invalid_argument("invalid input: invalid char seq");
            entity.name[j] = input[i];
            ++j;
            ++i;
        }

        while (j < VARCHAR_CAPACITY) {
            entity.name[j] = '\0';
            ++j;
        }

        j = 0;

        while (input[++i] == ' ') {}
        if (input[i] == '\0') throw std::invalid_argument("invalid input: end of line");

        while (input[i] != ',') {
            if (input[i] == '\0' || j == VARCHAR_CAPACITY) throw std::invalid_argument("invalid input: invalid char seq");
            entity.surname[j] = input[i];
            ++j;
            ++i;
        }

        while (j < VARCHAR_CAPACITY) {
            entity.surname[j] = '\0';
            ++j;
        }

        j = 0;

        while (input[++i] == ' ') {}
        if (input[i] == '\0') throw std::invalid_argument("invalid input: end of line");

        while (input[i] != ',') {
            if (input[i] == '\0' || j == VARCHAR_CAPACITY) throw std::invalid_argument("invalid input: invalid char seq");
            entity.patronymic[j] = input[i];
            ++j;
            ++i;
        }

        while (j < VARCHAR_CAPACITY) {
            entity.patronymic[j] = '\0';
            ++j;
        }

        while (input[++i] == ' ') {}
        if (input[i] == '\0') throw std::invalid_argument("invalid input: end of line");

        entity.timestamp = 0;
        int pow = 0;

        if (input[i] < 49 || input[i] > 57) throw std::invalid_argument("invalid input");

        do {
            if (input[i] < 48 || input[i] > 57) throw std::invalid_argument("invalid input");
            if (input[i] == ' ') continue;
            entity.timestamp *= 10;
            entity.timestamp += input[i] - 48;
        } while (input[++i] != ')');

        return is;
    }
};


#endif //OSLAB2_ENTITY_H

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
    long key {0};
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
        int i = 0, j = 0;
        char c;

        do {c = is.get();} while (c == ' ');
        if (c == '\0') throw std::invalid_argument("invalid input: end of line");

        if (c != '(') throw std::invalid_argument("invalid input: opening fail");

        do {c = is.get();} while (c == ' ');
        if (c == '\0') throw std::invalid_argument("invalid input: end of line");

        while (c != ',') {
            if (c == '\0' || j == VARCHAR_CAPACITY) throw std::invalid_argument("invalid input: invalid char seq");
            entity.name[j] = c;
            c = is.get();
            ++j;
        }

        while (j < VARCHAR_CAPACITY) {
            entity.name[j] = '\0';
            ++j;
        }

        j = 0;

        do {c = is.get();} while (c == ' ');
        if (c == '\0') throw std::invalid_argument("invalid input: end of line");

        while (c != ',') {
            if (c == '\0' || j == VARCHAR_CAPACITY) throw std::invalid_argument("invalid input: invalid char seq");
            entity.surname[j] = c;
            c = is.get();
            ++j;
        }

        while (j < VARCHAR_CAPACITY) {
            entity.surname[j] = '\0';
            ++j;
        }

        j = 0;

        do {c = is.get();} while (c == ' ');
        if (c == '\0') throw std::invalid_argument("invalid input: end of line");

        while (c != ',') {
            if (c == '\0' || j == VARCHAR_CAPACITY) throw std::invalid_argument("invalid input: invalid char seq");
            entity.patronymic[j] = c;
            c = is.get();
            ++j;
        }

        while (j < VARCHAR_CAPACITY) {
            entity.patronymic[j] = '\0';
            ++j;
        }

        do {c = is.get();} while (c == ' ');
        if (c == '\0') throw std::invalid_argument("invalid input: end of line");

        entity.timestamp = 0;

        if (c < 49 || c > 57) throw std::invalid_argument("invalid input");

        do {
            if (c == ' ') continue;
            if (c < 48 || c > 57) throw std::invalid_argument("invalid input");
            entity.timestamp *= 10;
            entity.timestamp += c - 48;
            c = is.get();
        } while (c != ')');

        return is;
    }
};


#endif //OSLAB2_ENTITY_H

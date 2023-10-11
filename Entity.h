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

    Entity(int key, const char* name, const char* surname, const char* patronymic, long timestamp);

    friend std::ostream& operator<<(std::ostream& os, const Entity& entity) {
        os << "entity {" << "key = " << entity.key
           << ", name = " << entity.name
           << ", surname = " << entity.surname
           << ", patronymic = " << entity.patronymic
           << ", timestamp = " << entity.timestamp
           << "}";
        return os;
    }
};


#endif //OSLAB2_ENTITY_H

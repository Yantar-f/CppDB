//
// Created by yantar on 09/10/23.
//

#ifndef OSLAB2_ENTITY_H
#define OSLAB2_ENTITY_H

#include <algorithm>

#define VARCHAR_SIZE (255)
#define VARCHAR_CAPACITY (VARCHAR_SIZE + 1)

typedef char varchar[VARCHAR_CAPACITY];

struct Entity {
    int key {0};
    varchar name;
    varchar surname;
    varchar patronymic;
    long timestamp {0};

    Entity(
        int key,
        const char* name,
        const char* surname,
        const char* patronymic,
        long timestamp
    ) : key(key) , timestamp(timestamp) {
        std::copy_n(name, VARCHAR_SIZE, this->name);
        std::copy_n(surname, VARCHAR_SIZE, this->surname);
        std::copy_n(patronymic, VARCHAR_SIZE, this->patronymic);
    }
};

#endif //OSLAB2_ENTITY_H

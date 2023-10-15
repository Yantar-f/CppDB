//
// Created by yantar on 11/10/23.
//

#include "Entity.h"

Entity::Entity(const char *name, const char *surname, const char *patronymic, long timestamp) : timestamp(timestamp) {
    std::copy_n(name, VARCHAR_SIZE, this->name);
    std::copy_n(surname, VARCHAR_SIZE, this->surname);
    std::copy_n(patronymic, VARCHAR_SIZE, this->patronymic);
}

Entity::Entity() {}

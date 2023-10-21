//
// Created by yantar on 09/10/23.
//
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "Repository.h"
#include "Entity.h"

#define FILE_ENTITY_CAPACITY (1000)
#define STRUCT_SIZE (sizeof(class Entity))
#define FILE_SIZE (FILE_ENTITY_CAPACITY * STRUCT_SIZE)
#define NO_CAPACITY (-1)

Repository::Repository(const char* filename) {
    logger.log_info("opening file");

    int file_descriptor = open(filename, O_RDWR|O_CREAT, (mode_t)0666);

    if (file_descriptor == -1) {
        logger.log_fatal("file can`t be reached");
        exit(1);
    }

    struct stat file_attrs;

    logger.log_info("getting file attrs");

    if (stat(filename, &file_attrs) == -1) {
        logger.log_fatal("file attrs can`t be reached");
        exit(1);
    }

    if (ftruncate(file_descriptor, FILE_SIZE) == -1) {
        logger.log_fatal("file truncate error");
    }

    logger.log_info("mapping file");

    initial_ptr = (Entity*) mmap(
        nullptr,
        FILE_SIZE,
        PROT_WRITE|PROT_READ,
        MAP_SHARED,
        file_descriptor,
        0
    );

    close(file_descriptor);

    if (initial_ptr == MAP_FAILED) {
        logger.log_fatal("file can`t be mapped");
        exit(1);
    }

    initiate_first_free_cell();
}

Repository::~Repository() {
    if (munmap((void*) initial_ptr, FILE_SIZE) == -1) {
        logger.log_fatal("unmapping file error");
        exit(1);
    }
}

void Repository::insert(Entity& entity) {
    if (first_free_cell == NO_CAPACITY) {
        logger.log_error("no capacity to save entity");
        return;
    }

    Entity* new_entity = initial_ptr + first_free_cell;

    new_entity->key = ++first_free_cell;
    new_entity->timestamp = entity.timestamp;

    std::copy_n(entity.name, VARCHAR_SIZE, new_entity->name);
    std::copy_n(entity.surname, VARCHAR_SIZE, new_entity->surname);
    std::copy_n(entity.patronymic, VARCHAR_SIZE, new_entity->patronymic);

    find_first_free_cell(first_free_cell);

    logger.log_info("entity saved");
}

std::vector<Entity*> Repository::select_all() {
    Entity* tmp_ptr = initial_ptr;
    std::vector<Entity*> entities;

    for (int i = 0; i < FILE_ENTITY_CAPACITY; ++i, ++tmp_ptr) {
        if (tmp_ptr->key != 0) entities.push_back(tmp_ptr);
    }

    logger.log_info(std::string{"entities received: "}.append(std::to_string(entities.size())).c_str());
    return entities;
}

std::vector<Entity*> Repository::select(ICondition& condition) {
    Entity* tmp_ptr = initial_ptr;
    std::vector<Entity*> entities;

    for (int i = 0; i < FILE_ENTITY_CAPACITY; ++i, ++tmp_ptr) {
        if (tmp_ptr->key != 0 && condition.is_matching(tmp_ptr)) entities.push_back(tmp_ptr);
    }

    logger.log_info(std::string{"entities received: "}.append(std::to_string(entities.size())).c_str());
    return entities;
}

void Repository::remove_all() {
    for (long i = 0; i < FILE_ENTITY_CAPACITY; ++i) {
        if (initial_ptr[i].key != 0) free_cell(i);
    }

    first_free_cell = 0;
    logger.log_info("all entities deleted");
}

void Repository::remove(ICondition& condition) {
    logger.log_info("deleting entities");

    Entity* tmp_ptr = initial_ptr;
    long i = 0, first_free_cell_initiating_range = first_free_cell == -1 ? FILE_ENTITY_CAPACITY : first_free_cell;

    while (i < first_free_cell_initiating_range) {
        if (tmp_ptr->key != 0 && condition.is_matching(tmp_ptr)) {
            free_cell(i);
            first_free_cell = i;
            break;
        }
        ++i;
        ++tmp_ptr;
    }

    ++i;
    ++tmp_ptr;

    while (i < FILE_ENTITY_CAPACITY) {
        if (tmp_ptr->key != 0 && condition.is_matching(tmp_ptr)) free_cell(i);
        ++i;
        ++tmp_ptr;
    }

    logger.log_info("entities deleted");
}

void Repository::update(Entity& updating_entity, ICondition &condition) {
    Entity* tmp_ptr = initial_ptr;
    int i = 0;

    while (i < FILE_ENTITY_CAPACITY) {
        if (tmp_ptr->key != 0 && condition.is_matching(tmp_ptr)) {
            if (updating_entity.name[0] != '\0') std::copy_n(updating_entity.name, VARCHAR_SIZE, tmp_ptr->name);
            if (updating_entity.name[0] != '\0') std::copy_n(updating_entity.surname, VARCHAR_SIZE, tmp_ptr->surname);
            if (updating_entity.name[0] != '\0') std::copy_n(updating_entity.patronymic, VARCHAR_SIZE, tmp_ptr->patronymic);
            if (updating_entity.timestamp != 0) tmp_ptr->timestamp = updating_entity.timestamp;
        }
        ++tmp_ptr;
        ++i;
    }
}

void Repository::initiate_first_free_cell() {
    find_first_free_cell(0);
}

void Repository::find_first_free_cell(long i) {
    while (i < FILE_ENTITY_CAPACITY) {
        if (initial_ptr[i].key == 0) {
            first_free_cell = i;
            return;
        }
        ++i;
    }

    first_free_cell = NO_CAPACITY;
    logger.log_warn("file is completely filled in");
}

void Repository::free_cell(long key) {
    Entity* entity = initial_ptr + key;
    entity->key = 0;
    entity->timestamp = 0;

    for (int i = 0; i < VARCHAR_SIZE; ++i) {
        entity->name[i] = '\0';
        entity->surname[i] = '\0';
        entity->patronymic[i] = '\0';
    }
}

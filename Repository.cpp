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
#define STRUCT_SIZE (sizeof(struct Entity))
#define FILE_SIZE (FILE_ENTITY_CAPACITY * STRUCT_SIZE)

Repository::Repository(const char *filename) {
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

void Repository::add(Entity &entity) {
    if (first_free_cell == -1) {
        logger.log_error("no capacity to save entity");
        return;
    }

    logger.log_info("saving entity");

    Entity* new_entity = initial_ptr + first_free_cell;

    new_entity->key = first_free_cell;
    new_entity->timestamp = entity.timestamp;
    /*
     *
     */

    find_first_free_cell(first_free_cell);

    if (first_free_cell == -1) logger.log_warn("file is completely filled in");

    logger.log_info("entity saved");
}

std::vector<Entity*> Repository::get_all() {
    logger.log_info("getting entities");

    Entity* tmp_ptr = initial_ptr;
    std::vector<Entity*> entities;

    for (int i = 0; i < FILE_ENTITY_CAPACITY; i++, tmp_ptr++) {
        if (tmp_ptr->key != 0) entities.push_back(tmp_ptr);
    }

    logger.log_info("entities received");
    return entities;
}

Entity* Repository::get_by_key(const int key) {
    logger.log_info("getting entities");

    if (key > FILE_ENTITY_CAPACITY) {
        logger.log_warn("query key out of bounds");
        return nullptr;
    }

    Entity* entity = initial_ptr + key - 1;

    logger.log_info("entities received");

    if (entity->key == 0) return nullptr;
    return entity;
}

std::vector<Entity*> Repository::get_by_condition(ICondition &condition) {
    logger.log_info("getting entities");

    Entity* tmp_ptr = initial_ptr;
    std::vector<Entity*> entities;

    for (int i = 0; i < FILE_ENTITY_CAPACITY; i++, tmp_ptr++) {
        if (condition.is_matching(tmp_ptr)) entities.push_back(tmp_ptr);
    }

    logger.log_info("entities received");
    return entities;
}

void Repository::delete_all() {
    logger.log_info("deleting entities");

    Entity* tmp_ptr = initial_ptr;

    for (int i = 0; i < FILE_ENTITY_CAPACITY; i++, tmp_ptr++) {
        if (tmp_ptr->key != 0) free_cell(tmp_ptr->key);
    }

    first_free_cell = 0;

    logger.log_info("all entities deleted");
}

void Repository::delete_by_condition(ICondition& condition) {
    logger.log_info("deleting entities");

    Entity* tmp_ptr = initial_ptr;
    int i = 0;

    while (i < first_free_cell) {
        if (tmp_ptr->key != 0 && condition.is_matching(tmp_ptr)) {
            free_cell(tmp_ptr->key);
            break;
        }
        ++i;
    }

    first_free_cell = i;

    while (i < FILE_ENTITY_CAPACITY) {
        if (tmp_ptr->key != 0 && condition.is_matching(tmp_ptr)) free_cell(tmp_ptr->key);
        ++i;
        ++tmp_ptr;
    }

    logger.log_info("entities deleted");
}

void Repository::initiate_first_free_cell() {
    for (int i = 0; i < FILE_ENTITY_CAPACITY; i++) {
        if (initial_ptr[i].key == 0) {
            first_free_cell = i;
            return;
        }
    }

    first_free_cell = -1;
}

void Repository::find_first_free_cell(int i) {
    while (i <  FILE_ENTITY_CAPACITY) {
        if (initial_ptr[i].key == 0) {
            first_free_cell = i;
            return;
        }
    }

    first_free_cell = -1;
}

void Repository::free_cell(int key) {
    Entity* entity = initial_ptr + key;
    entity->key = 0;
    entity->timestamp = 0;

    for (int i = 0; i < VARCHAR_SIZE; i++) {
        entity->name[i] = '\0';
        entity->surname[i] = '\0';
        entity->patronymic[i] = '\0';
    }
}

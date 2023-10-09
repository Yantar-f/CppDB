//
// Created by yantar on 09/10/23.
//

#ifndef OSLAB2_REPOSITORY_H
#define OSLAB2_REPOSITORY_H

#include <vector>
#include "Logger.h"
#include "Entity.h"
#include "ICondition.h"

class Repository {
private:
    Logger logger {"Repository"};
    Entity* initial_ptr {nullptr};
    int first_free_cell {-1};
public:
    explicit Repository(const char* filename);
    ~Repository();
    std::vector<Entity*> get_all();
    void add(Entity&  entity);
    Entity* get_by_key(int key);
    std::vector<Entity*> get_by_condition(ICondition& condition);
    void delete_all();
    void delete_by_condition(ICondition& condition);
private:
    void initiate_first_free_cell();
    void find_first_free_cell(int i);
    void free_cell(int key);
};

#endif //OSLAB2_REPOSITORY_H

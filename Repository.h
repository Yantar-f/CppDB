//
// Created by yantar on 09/10/23.
//

#ifndef OSLAB2_REPOSITORY_H
#define OSLAB2_REPOSITORY_H

#include <vector>
#include "Logger.h"
#include "Entity.h"
#include "Conditions/ICondition.h"

class Repository {
private:
    Logger logger {"Repository"};
    Entity* initial_ptr {nullptr};
    long first_free_cell {-1};
public:
    explicit Repository(const char* filename);
    ~Repository();
    std::vector<Entity*> select_all();
    std::vector<Entity*> select(ICondition& condition);
    void insert(Entity&  entity);
    void remove_all();
    void remove(ICondition& condition);
    void update(Entity& updating_entity, ICondition& condition);
private:
    void initiate_first_free_cell();
    void find_first_free_cell(long i);
    void free_cell(long key);
};

#endif //OSLAB2_REPOSITORY_H

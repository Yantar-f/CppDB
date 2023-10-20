//
// Created by yantar on 15/10/23.
//

#ifndef DBLAB_PATRONYMICEQUALSCONDITION_H
#define DBLAB_PATRONYMICEQUALSCONDITION_H


#include "../Entity.h"
#include "VarcharEqualsCondition.h"

class PatronymicEqualsCondition : public VarcharEqualsCondition{
public:
    PatronymicEqualsCondition(std::string comparing_patronymic);
    bool is_matching(Entity* entity) override;
};


#endif //DBLAB_PATRONYMICEQUALSCONDITION_H

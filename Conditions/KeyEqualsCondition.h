//
// Created by yantar on 20/10/23.
//

#ifndef DBLAB_KEYEQUALSCONDITION_H
#define DBLAB_KEYEQUALSCONDITION_H


#include "ICondition.h"

class KeyEqualsCondition : public ICondition {
    long comparing_key;
public:
    KeyEqualsCondition(long comparing_key);
    bool is_matching(Entity* entity) override;
};


#endif //DBLAB_KEYEQUALSCONDITION_H

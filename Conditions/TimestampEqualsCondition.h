//
// Created by yantar on 20/10/23.
//

#ifndef DBLAB_TIMESTAMPEQUALSCONDITION_H
#define DBLAB_TIMESTAMPEQUALSCONDITION_H


#include "ICondition.h"

class TimestampEqualsCondition : public ICondition {
    long comparing_timestamp;
public:
    TimestampEqualsCondition(long comparing_timestamp);
    bool is_matching(Entity* entity) override;
};


#endif //DBLAB_TIMESTAMPEQUALSCONDITION_H

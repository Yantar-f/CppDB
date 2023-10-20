//
// Created by yantar on 20/10/23.
//

#ifndef DBLAB_TIMESTAMPBTWNCONDITION_H
#define DBLAB_TIMESTAMPBTWNCONDITION_H


#include "ICondition.h"

class TimestampBtwnCondition : public ICondition {
    long start, end;
public:
    TimestampBtwnCondition(long start, long end);
    bool is_matching(Entity* entity) override;
};


#endif //DBLAB_TIMESTAMPBTWNCONDITION_H

#ifndef MAP_BOSS_H_
#define MAP_BOSS_H_
#include "Map.h"

class MapBoss : public Map
{
public:
    MapBoss(LP& LP);
    ~MapBoss() override;
};

#endif
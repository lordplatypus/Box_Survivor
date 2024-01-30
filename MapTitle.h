#ifndef MAP_TITLE_H_
#define MAP_TITLE_H_
#include "Map.h"

class MapTitle : public Map
{
public:
    MapTitle(LP& LP);
    ~MapTitle() override;
};

#endif
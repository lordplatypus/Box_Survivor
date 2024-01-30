#ifndef MAPNULL_H_
#define MAPNULL_H_
#include "Map.h"

class MapNull : public Map
{
public:
    virtual const bool Transversable(const sf::Vector2f& position) const override {return true;}
    virtual const int GetTile(const sf::Vector2i& tilePosition) const override {return 0;}
};

#endif
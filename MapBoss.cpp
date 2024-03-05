#include "MapBoss.h"
#include "ID.h"

MapBoss::MapBoss(LP& LP)
{
    LP_ = &LP;

    ResizeMap(sf::Vector2i(64, 64));
    SetMapFromCSV("./Map_Boss.csv");
    SetTileMap(tileset_texture);
}

MapBoss::~MapBoss()
{}
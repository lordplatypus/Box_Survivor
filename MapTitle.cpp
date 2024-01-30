#include "MapTitle.h"
#include "ID.h"

MapTitle::MapTitle(LP& LP)
{
    LP_ = &LP;

    ResizeMap(sf::Vector2i(45, 25));
    SetMapFromCSV("./Map_Title.csv");
    SetTileMap(tileset_texture);
}

MapTitle::~MapTitle()
{}
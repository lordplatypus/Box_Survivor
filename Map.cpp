#include "Map.h"
#include "ID.h"
#include <fstream>

Map::Map()
{}

Map::~Map()
{}

void Map::Draw(Camera& camera) const
{
    camera.Draw(tileMap_, layer_tilemap);
}

void Map::ResizeMap(const sf::Vector2i& size)
{
    std::vector<int> resize(size.y);
    map_.resize(size.x, resize);
    mapSize_ = size;
}

void Map::SetMapFromCSV(const std::string& CSVFilePath)
{
    std::ifstream mapData(CSVFilePath);
    char dummy;

    for (int y = 0; y < mapSize_.y; y++)
    {
        for (int x = 0; x < mapSize_.x; x++)
        {
            mapData >> map_[x][y];
            if (x < mapSize_.x - 1) 
            {
                mapData >> dummy;
            }
        }
    }
    mapData.close();
}

void Map::SetTileMap(const int tileset_texture)
{
    tileMap_ = LP_->SetTileMap(tileset_texture, sf::Vector2u(tileSize, tileSize), map_, sf::Vector2f(0.0f, 0.0f), mapSize_.x, mapSize_.y);
}

const bool Map::Transversable(const sf::Vector2f& position) const
{
    sf::Vector2i worldToTileCoords = sf::Vector2i((int)position.x / tileSize, (int)position.y / tileSize);
    if (GetTile(worldToTileCoords) != -1) return false;
    else return true;
}

const int Map::GetTile(const sf::Vector2i& tilePosition) const
{
    return map_[tilePosition.x][tilePosition.y];
}
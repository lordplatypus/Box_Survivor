#ifndef MAP_H_
#define MAP_H_
#include <SFML/Graphics.hpp>
#include <vector>
#include "Camera.h"
#include "LP.h"

class Map
{
public:
    Map();
    virtual ~Map();

    virtual void Draw(Camera& camera) const;
    virtual void ResizeMap(const sf::Vector2i& size);
    virtual void SetMapFromCSV(const std::string& CSVFilePath);
    virtual void SetTileMap(const int tileset_texture);
    virtual const bool Transversable(const sf::Vector2f& position) const;
    virtual const int GetTile(const sf::Vector2i& tilePosition) const;
    

protected:
    const int tileSize{32};
    LP* LP_{nullptr};
    sf::Vector2i mapSize_{0, 0};
    std::vector<std::vector<int>> map_;
    TileMap tileMap_;
};

#endif
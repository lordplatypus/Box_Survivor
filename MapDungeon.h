#ifndef MAP_DUNGEON_H_
#define MAP_DUNGEON_H_
#include "Map.h"

class MapDungeon : public Map
{
public:
    MapDungeon(LP& LP, int number_of_rooms);
    ~MapDungeon() override;

    sf::Vector2i GetPlayerSpawnPos();
    sf::Vector2i GetObjectSpawnPos();

private:
    void RandomizeMap(int number_of_rooms);
    void BuildRoomMap();
    void BuildMap();
    void SetRoomFromCSV(const std::string& CSVFilePath, const sf::Vector2i& roomPosition, const sf::Vector2i& roomSize);
    void SetBlankRoom(const sf::Vector2i& roomPosition, const sf::Vector2i& roomSize);
    void CreateHallway(const sf::Vector2i& roomCoordinate);

private:
    int number_of_rooms_{0};
    std::vector<std::vector<int>> room_map_; // 2d map
    std::vector<sf::Vector2i> room_coords_; // vector of all room coords
    sf::Vector2i player_room_; // room coords for where the player spawns
};

#endif
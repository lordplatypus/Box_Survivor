#include <iostream>
#include <fstream>
#include "MapDungeon.h"
#include "ID.h"

MapDungeon::MapDungeon(LP& LP, int number_of_rooms)
{
    LP_ = &LP;
    number_of_rooms_ = number_of_rooms;

    RandomizeMap(number_of_rooms_);
}

MapDungeon::~MapDungeon()
{}

sf::Vector2i MapDungeon::GetPlayerSpawnPos()
{
    int room_id = std::rand() / ((RAND_MAX + 1u) / room_coords_.size());
    player_room_ = room_coords_[room_id];
    int world_x = (player_room_.x * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
    int world_y = (player_room_.y * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
    sf::Vector2i player_world_pos(world_x, world_y);
    while (!Transversable(sf::Vector2f(player_world_pos.x, player_world_pos.y)))
    {
        world_x = (player_room_.x * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
        world_y = (player_room_.y * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
        player_world_pos = sf::Vector2i(world_x, world_y);
    }
    return player_world_pos;
}

sf::Vector2i MapDungeon::GetObjectSpawnPos()
{ 
    int room_id = std::rand() / ((RAND_MAX + 1u) / room_coords_.size());
    while (player_room_ == room_coords_[room_id])
    {
        room_id = std::rand() / ((RAND_MAX + 1u) / room_coords_.size());   
    }
    int world_x = (room_coords_[room_id].x * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
    int world_y = (room_coords_[room_id].y * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
    sf::Vector2i object_world_pos(world_x, world_y);
    while (!Transversable(sf::Vector2f(object_world_pos.x, object_world_pos.y)))
    {
        world_x = (room_coords_[room_id].x * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
        world_y = (room_coords_[room_id].y * 24 + 2 + std::rand() / ((RAND_MAX + 1u) / 20)) * tileSize;
        object_world_pos = sf::Vector2i(world_x, world_y);
    }
    return object_world_pos;
}

void MapDungeon::RandomizeMap(int number_of_rooms)
{
    BuildRoomMap();
    
    ResizeMap(sf::Vector2i(room_map_[0].size()*24, room_map_.size()*24));

    BuildMap();

    SetTileMap(tileset_texture);
}

void MapDungeon::BuildRoomMap()
{
    int max_x = number_of_rooms_ * 2 + 1;
    int max_y = number_of_rooms_ * 2 + 1;
    std::vector<std::vector<int>> room_map(max_x, std::vector<int>(max_y));

    std::srand(std::time(nullptr));

    int rooms_to_place = number_of_rooms_;
    int failsafe = 100;
    int x = number_of_rooms_;
    int y = number_of_rooms_;
    sf::Vector2i min(number_of_rooms_, number_of_rooms_);
    sf::Vector2i max(number_of_rooms_, number_of_rooms_);

    while (rooms_to_place > 0 && failsafe > 0)
    {
        failsafe--;
        int random_room = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
        switch (random_room) // random value between 1-6
        {
            default:
                break;

            case 1:
            case 2:
                if (room_map[y][x] == 0) 
                {
                    room_map[y][x] = random_room;
                    rooms_to_place--;
                    if (x < min.x) min.x = x;
                    if (y < min.y) min.y = y;
                    if (x > max.x) max.x = x;
                    if (y > max.y) max.y = y;
                }
                break;

            case 3:
            case 4:
                if (room_map[y][x] == 0) 
                {
                    if (x+1 < max_x && room_map[y][x+1] == 0)
                    {
                        room_map[y][x] = random_room;
                        room_map[y][x+1] = random_room;
                        rooms_to_place--;
                        if (x < min.x) min.x = x;
                        if (y < min.y) min.y = y;
                        if (x+1 > max.x) max.x = x+1;
                        if (y > max.y) max.y = y;
                    }
                    else if (x-1 >= 0 && room_map[y][x-1] == 0)
                    {
                        room_map[y][x] = random_room;
                        room_map[y][x-1] = random_room;
                        rooms_to_place--;
                        if (x-1 < min.x) min.x = x-1;
                        if (y < min.y) min.y = y;
                        if (x > max.x) max.x = x;
                        if (y > max.y) max.y = y;
                    }
                    else
                    { // contingency plan
                        // random_room = 1 + std::rand() / ((RAND_MAX + 1u) / 2);
                        room_map[y][x] = 1;
                        rooms_to_place--;
                        if (x < min.x) min.x = x;
                        if (y < min.y) min.y = y;
                        if (x > max.x) max.x = x;
                        if (y > max.y) max.y = y;
                    }
                }
                break;

            case 5:
            case 6:
                if (room_map[y][x] == 0) 
                {
                    if (y+1 < max_y * 2 + 1 && room_map[y+1][x] == 0)
                    {
                        room_map[y][x] = random_room;
                        room_map[y+1][x] = random_room;
                        rooms_to_place--;
                        if (x < min.x) min.x = x;
                        if (y < min.y) min.y = y;
                        if (x > max.x) max.x = x;
                        if (y+1 > max.y) max.y = y+1;
                    }
                    else if (y-1 >= 0 && room_map[y-1][x] == 0)
                    {
                        room_map[y][x] = random_room;
                        room_map[y-1][x] = random_room;
                        rooms_to_place--;
                        if (x < min.x) min.x = x;
                        if (y-1 < min.y) min.y = y-1;
                        if (x > max.x) max.x = x;
                        if (y > max.y) max.y = y;
                    }
                    else
                    { // contingency plan
                        // random_room = 1 + std::rand() / ((RAND_MAX + 1u) / 2);
                        room_map[y][x] = 1;
                        rooms_to_place--;
                        if (x < min.x) min.x = x;
                        if (y < min.y) min.y = y;
                        if (x > max.x) max.x = x;
                        if (y > max.y) max.y = y;
                    }
                }
                break;
        }

        switch (std::rand() / ((RAND_MAX + 1u) / 4))
        {
            default:
                break;
            case 0:
                if (x > 0) x--;
                break;
            case 1:
                if (x < max_x) x++;
                break;
            case 2:
                if (y > 0) y--;
                break;
            case 3:
                if (y < max_y) y++;
                break;
        }
    }

    std::vector<int> resize(max.x - min.x + 1);
    room_map_.resize(max.y - min.y + 1, resize);

    for (y = 0; y < room_map_.size(); y++)
    {
        for (x = 0; x < room_map_[0].size(); x++)
        {
            room_map_[y][x] = room_map[y+min.y][x+min.x];
            std::cout << room_map_[y][x];
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

void MapDungeon::BuildMap()
{
    std::vector<std::vector<int>> placed_rooms(room_map_.size(), std::vector<int>(room_map_[0].size()));
    for (int y = 0; y < room_map_.size(); y++)
    {
        for (int x = 0; x < room_map_[0].size(); x++)
        {
            sf::Vector2i room_to_world(x*24, y*24);
            switch (room_map_[y][x])
            {
                default:
                case 0:
                    SetBlankRoom(room_to_world, sf::Vector2i(24, 24));
                    break;
                case 1:
                    SetRoomFromCSV("./Resources/Room1.csv", room_to_world, sf::Vector2i(24, 24));
                    room_coords_.push_back(sf::Vector2i(x, y));
                    break;
                case 2:
                    SetRoomFromCSV("./Resources/Room2.csv", room_to_world, sf::Vector2i(24, 24));
                    room_coords_.push_back(sf::Vector2i(x, y));
                    break;
                case 3:
                    if (x+1 < room_map_[0].size() && placed_rooms[y][x] == 0) 
                    {
                        SetRoomFromCSV("./Resources/Room3.csv", room_to_world, sf::Vector2i(24*2, 24));
                        placed_rooms[y][x+1] = 1;
                        room_coords_.push_back(sf::Vector2i(x, y));
                        room_coords_.push_back(sf::Vector2i(x+1, y));
                    }
                    break;
                case 4:
                    if (x+1 < room_map_[0].size() && placed_rooms[y][x] == 0) 
                    {
                        SetRoomFromCSV("./Resources/Room4.csv", room_to_world, sf::Vector2i(24*2, 24));
                        placed_rooms[y][x+1] = 1;
                        room_coords_.push_back(sf::Vector2i(x+1, y));
                    }
                    break;
                case 5:
                    if (y+1 < room_map_.size() && placed_rooms[y][x] == 0) 
                    {
                        SetRoomFromCSV("./Resources/Room5.csv", room_to_world, sf::Vector2i(24, 24*2));
                        placed_rooms[y+1][x] = 1;
                        room_coords_.push_back(sf::Vector2i(x, y));
                        room_coords_.push_back(sf::Vector2i(x, y+1));
                    }
                    break;
                case 6:
                    if (y+1 < room_map_.size() && placed_rooms[y][x] == 0) 
                    {
                        SetRoomFromCSV("./Resources/Room6.csv", room_to_world, sf::Vector2i(24, 24*2));
                        placed_rooms[y+1][x] = 1;
                        room_coords_.push_back(sf::Vector2i(x, y));
                        room_coords_.push_back(sf::Vector2i(x, y+1));
                    }
                    break;
            }
            placed_rooms[y][x] = 1;
        }
    }

    for (int y = 0; y < room_map_.size(); y++)
    {
        for (int x = 0; x < room_map_[0].size(); x++)
        {
            if (room_map_[y][x] != 0) CreateHallway(sf::Vector2i(x, y));
        }
    }
}

void MapDungeon::SetRoomFromCSV(const std::string& CSVFilePath, const sf::Vector2i& roomPosition, const sf::Vector2i& roomSize)
{
    std::ifstream roomData(CSVFilePath);
    char dummy;

    for (int y = 0; y < roomSize.y; y++)
    {
        for (int x = 0; x < roomSize.x; x++)
        {
            roomData >> map_[x+roomPosition.x][y+roomPosition.y];
            if (x < roomSize.x - 1) 
            {
                roomData >> dummy;
            }
        }
    }
    roomData.close();
}

void MapDungeon::SetBlankRoom(const sf::Vector2i& roomPosition, const sf::Vector2i& roomSize)
{
    for (int y = 0; y < roomSize.y; y++)
    {
        for (int x = 0; x < roomSize.x; x++)
        {
            map_[x+roomPosition.x][y+roomPosition.y] = -1;
        }
    }
}

void MapDungeon::CreateHallway(const sf::Vector2i& roomCoordinate)
{
    int x = roomCoordinate.x;
    int y = roomCoordinate.y;
    int room_id = room_map_[y][x];
    if (x - 1 >= 0 && room_map_[y][x-1] != 0)
    { // left
        int map_x = x * 24;
        int map_y = y * 24 + 10;
        for (int i = map_y; i < map_y + 4; i++)
        {
            map_[map_x][i] = -1;
        }
    }
    if (x + 1 < room_map_[0].size() && room_map_[y][x+1] != 0)
    { // right
        int map_x = x * 24 + 23;
        int map_y = y * 24 + 10;
        for (int i = map_y; i < map_y + 4; i++)
        {
            map_[map_x][i] = -1;
        }
    }
    if (y - 1 >= 0 && room_map_[y-1][x] != 0)
    { // up
        int map_x = x * 24 + 10;
        int map_y = y * 24;
        for (int i = map_x; i < map_x + 4; i++)
        {
            map_[i][map_y] = -1;
        }
    }
    if (y + 1 < room_map_.size() && room_map_[y+1][x] != 0)
    { // down
        int map_x = x * 24 + 10;
        int map_y = y * 24 + 23;
        for (int i = map_x; i < map_x + 4; i++)
        {
            map_[i][map_y] = -1;
        }
    }
}
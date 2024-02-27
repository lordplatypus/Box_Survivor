#include "SceneFloor1.h"

SceneFloor1::SceneFloor1(Game* game)
{
    game_ = game;
}

SceneFloor1::~SceneFloor1()
{}

void SceneFloor1::Init()
{
    if (!GetPause())
    {
        DungeonInit(5, 25, "Title");
    }
    else
    {
        SetPause(false);
        playerManager_->UpdateUI();
    }
}
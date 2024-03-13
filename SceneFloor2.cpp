#include "SceneFloor2.h"

SceneFloor2::SceneFloor2(Game* game)
{
    game_ = game;
}

SceneFloor2::~SceneFloor2()
{}

void SceneFloor2::Init()
{
    if (!GetPause())
    {
        DungeonInit(10, 50, "Floor3");
    }
    else
    {
        SetPause(false);
        playerManager_->UpdateUI();
    }
}
#include "SceneFloor3.h"

SceneFloor3::SceneFloor3(Game* game)
{
    game_ = game;
}

SceneFloor3::~SceneFloor3()
{}

void SceneFloor3::Init()
{
    if (!GetPause())
    {
        DungeonInit(20, 100, "Boss");
    }
    else
    {
        SetPause(false);
        playerManager_->UpdateUI();
    }
}
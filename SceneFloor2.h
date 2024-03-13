#ifndef SCENE_FLOOR_2_H_
#define SCENE_FLOOR_2_H_
#include "SceneDungeon.h"

class SceneFloor2 : public SceneDungeon
{
public:
    SceneFloor2(Game* game);
    ~SceneFloor2();
    virtual void Init() override;
};

#endif
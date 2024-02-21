#ifndef SCENE_FLOOR_1_H_
#define SCENE_FLOOR_1_H_
#include "SceneDungeon.h"

class SceneFloor1 : public SceneDungeon
{
public:
    SceneFloor1(Game* game);
    ~SceneFloor1();
    virtual void Init() override;
};

#endif
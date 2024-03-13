#ifndef SCENE_FLOOR_3_H_
#define SCENE_FLOOR_3_H_
#include "SceneDungeon.h"

class SceneFloor3 : public SceneDungeon
{
public:
    SceneFloor3(Game* game);
    ~SceneFloor3();
    virtual void Init() override;
};

#endif
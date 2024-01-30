#ifndef SCENE_TITLE_H_
#define SCENE_TITLE_H_
#include "Scene.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "ParticleManager.h"
#include "MapTitle.h"


class SceneTitle : public Scene
{
public:
    SceneTitle(Game* game);
    ~SceneTitle();
    virtual void Init() override;
    virtual void Update(float delta_time) override;
    virtual void Draw(Camera& camera) const override;
    virtual void AddGameObject(GameObject* gameObject) override;
    virtual GameObject* FindGameObject(const std::string& string, const bool byName = true, const bool byTag = false, const bool byID = false) override;
    virtual void ChangeScene(const std::string& sceneName) override;
    virtual void End() override;

private:
    Game* game_{nullptr};
    GameObjectManager gom_;
    ParticleManager pm_;
    MapTitle* mt_{nullptr};
    bool changeSceneFlag_{false};
    std::string sceneName_;
};

#endif
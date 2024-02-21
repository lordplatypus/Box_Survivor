#ifndef SCENE_DUNGEON_H_
#define SCENE_DUNGEON_H_
#include "Scene.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "PlayerManager.h"
#include "MapDungeon.h"

class SceneDungeon : public Scene
{
public:
    // SceneDungeon(Game* game);
    // ~SceneDungeon();
    // virtual void Init() override;
    virtual void Update(float delta_time) override;
    virtual void Draw(Camera& camera) const override;
    virtual void AddGameObject(GameObject* gameObject) override;
    virtual GameObject* FindGameObject(const std::string& string, const bool byName = true, const bool byTag = false, const bool byID = false) override;
    virtual void ChangeScene(const std::string& sceneName) override;
    virtual void End() override;

    void DungeonInit(int dungeonRoomNum, int enemyNum, const std::string& nextSceneName);
private:
    virtual void RandomEnemyPlacement(int enemyNum);
    void SetRandomChallenge(const std::string& nextSceneName);
public:
    void SetEnemyCount(int enemyCount);
    const int GetEnemyCount() const;
    void SetPause(bool pause);
    const bool GetPause() const;

protected:
    Game* game_{nullptr};
    GameObjectManager gom_;
    bool changeSceneFlag_{false};
    std::string sceneName_;
    PlayerManager* playerManager_{nullptr};
    MapDungeon* md_{nullptr};
    int enemyCount_{0};
    bool pause_{false};
};

#endif
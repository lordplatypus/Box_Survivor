#include "SceneDungeon.h"
#include "Staircase.h"
#include "ChallengeKills.h"
#include "EnemyZombie.h"
#include "EnemySlime.h"
#include "EnemyShooter.h"

void SceneDungeon::Update(float delta_time)
{
    gom_.Update(delta_time); //update all gameobjects
    gom_.Collision(); //check collision between gameobjects
    gom_.Remove(); //remove "dead" gameobjects
    if (changeSceneFlag_)
    {
        changeSceneFlag_ = false;
        game_->ChangeScene(sceneName_);
    }
}

void SceneDungeon::Draw(Camera& camera) const
{
    md_->Draw(camera);
    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
}

void SceneDungeon::AddGameObject(GameObject* gameObject)
{
    gom_.Add(gameObject); //add gameobject to the list of gameobjects
}

GameObject* SceneDungeon::FindGameObject(const std::string& string, const bool byName, const bool byTag, const bool byID)
{//if byTag and byID are both left to default (false), search by name
    return gom_.Find(string, byName, byTag, byID); //returns a GameObject, returns a nullptr if the GameObject is not found
}

void SceneDungeon::ChangeScene(const std::string& sceneName)
{
    sceneName_ = sceneName;
    changeSceneFlag_ = true;
    if (sceneName == "Upgrade") SetPause(true);
}

void SceneDungeon::End()
{
    if (pause_) return;
    gom_.Clear();
    delete(md_);
    delete(playerManager_);
}

void SceneDungeon::DungeonInit(int dungeonRoomNum, int enemyNum, const std::string& nextSceneName)
{
    md_ = new MapDungeon(game_->GetLP(), dungeonRoomNum); // build map
    sf::Vector2i player_pos = md_->GetPlayerSpawnPos(); // get player spawn position and mark room as a non-spawn room for other objects
    // Create player and player manager
    Player* player = new Player(*this, game_->GetCamera(), *md_, game_->GetPlayerStats(), sf::Vector2f(player_pos.x, player_pos.y));
    playerManager_ = new PlayerManager(game_->GetPlayerStats(), *player, *this, game_->GetCamera(), game_->GetLP());
    AddGameObject(player);
    // place enemies
    RandomEnemyPlacement(enemyNum);
    // Create floor challenge and staircase to next floor
    SetRandomChallenge(nextSceneName);
}

void SceneDungeon::RandomEnemyPlacement(int enemyNum)
{
    for (int i = 0; i < enemyNum; i++)
    {
        sf::Vector2i enemy_pos = md_->GetObjectSpawnPos();
        int randEnemyID = std::rand() / ((RAND_MAX + 1u) / 3);
        switch (randEnemyID)
        {
            default:
                AddGameObject(new EnemyZombie(*this, *md_, *playerManager_, enemyCount_, sf::Vector2f(enemy_pos.x, enemy_pos.y)));
                break;
            
            case 1:
                AddGameObject(new EnemySlime(*this, *md_, *playerManager_, enemyCount_, sf::Vector2f(enemy_pos.x, enemy_pos.y), sf::Vector2f(32, 32)));
                enemyCount_ += 6; // because slime breaks up into 6 more 
                break;
            
            case 2:
                AddGameObject(new EnemyShooter(*this, *md_, *playerManager_, enemyCount_, sf::Vector2f(enemy_pos.x, enemy_pos.y)));
                break;
        }
        enemyCount_++;
    }
}

void SceneDungeon::SetRandomChallenge(const std::string& nextSceneName)
{
    sf::Vector2i stair_pos = md_->GetObjectSpawnPos();
    Staircase* staircase = new Staircase(*this, sf::Vector2f(stair_pos.x, stair_pos.y), nextSceneName);
    AddGameObject(staircase);

    // int challenge_id = std::rand() / ((RAND_MAX + 1u) / NUMBER OF CHALLENGES);
    int challenge_id = 0;
    switch (challenge_id)
    {
        default:
            AddGameObject(new ChallengeKills(*this, *playerManager_, *staircase, GetEnemyCount(), 1 + std::rand() / ((RAND_MAX + 1u) / GetEnemyCount())));
            break;
    }
}

void SceneDungeon::SetEnemyCount(int enemyCount)
{
    enemyCount_ = enemyCount;
}

const int SceneDungeon::GetEnemyCount() const
{
    return enemyCount_;
}

void SceneDungeon::SetPause(bool pause)
{
    pause_ = pause;
}

const bool SceneDungeon::GetPause() const
{
    return pause_;
}
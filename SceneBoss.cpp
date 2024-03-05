#include "SceneBoss.h"
#include "LP.h"
#include "ID.h"
#include "Player.h"
#include "EnemyBoss.h"
#include "EnemyBomb.h"

SceneBoss::SceneBoss(Game* game) : game_{game}
{}

SceneBoss::~SceneBoss()
{}

void SceneBoss::Init()
{
    mb_ = new MapBoss(game_->GetLP());

    Player* player = new Player(*this, game_->GetCamera(), *mb_, game_->GetPlayerStats(), sf::Vector2f(64 * 32 / 2 - 16, 48 * 32));
    playerManager_ = new PlayerManager(game_->GetPlayerStats(), *player, *this, game_->GetCamera(), game_->GetLP());

    AddGameObject(player);
    AddGameObject(new EnemyBoss(*this, *mb_, *playerManager_, game_->GetCamera(), game_->GetLP(), sf::Vector2f(64 * 32 / 2, 64 * 32 / 2)));

    // AddGameObject(new EnemyBomb(*playerManager_, sf::Vector2f(64 * 32 / 2 - 16, 48 * 32), 1.0f));

    game_->GetCamera().SetViewCenter(view_main, sf::Vector2f(0, 0));
}

void SceneBoss::Update(float delta_time)
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

void SceneBoss::Draw(Camera& camera) const
{
    mb_->Draw(camera);

    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
}

void SceneBoss::AddGameObject(GameObject* gameObject)
{
    gom_.Add(gameObject); //add gameobject to the list of gameobjects
}

GameObject* SceneBoss::FindGameObject(const std::string& string, const bool byName, const bool byTag, const bool byID)
{//if byTag and byID are both left to default (false), search by name
    return gom_.Find(string, byName, byTag, byID); //returns a GameObject, returns a nullptr if the GameObject is not found
}

void SceneBoss::ChangeScene(const std::string& sceneName)
{
    // game_->ChangeScene(sceneName);
    sceneName_ = sceneName;
    changeSceneFlag_ = true;
}

void SceneBoss::End()
{
    gom_.Clear();
    delete(mb_);
    delete(playerManager_);
}
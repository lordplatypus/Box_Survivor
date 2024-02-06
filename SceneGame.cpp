#include "SceneGame.h"
#include "LP.h"
#include "ID.h"
#include "ExampleObject.h"
#include "Player.h"
#include "UIHP.h"
#include "UIExp.h"
#include "Staircase.h"
#include "MapNull.h"

SceneGame::SceneGame(Game* game) : game_{game}
{}

SceneGame::~SceneGame()
{}

void SceneGame::Init()
{
    //AddGameObject(new Object(position, &pm_, this)); Example
    
    MapNull* nullMap = new MapNull();
    Player* player = new Player(*this, game_->GetCamera(), *nullMap, game_->GetPlayerStats(), sf::Vector2f(45 / 2 * 32, 25 / 2 * 32));
    UIHP* player_hp_ui = new UIHP(game_->GetPlayerStats().GetMaxHP(), game_->GetPlayerStats().GetHP(), sf::Vector2f(32, game_->GetCamera().GetView(view_UI).getSize().y - 64));
    UIExp* player_exp_ui = new UIExp(game_->GetPlayerStats().GetMaxExperience(), game_->GetPlayerStats().GetExperience(), sf::Vector2f(game_->GetCamera().GetView(view_UI).getSize().x - 320 - 32, game_->GetCamera().GetView(view_UI).getSize().y - 64));
    playerManager_ = new PlayerManager(game_->GetPlayerStats(), *player, *player_hp_ui, *player_exp_ui);

    AddGameObject(player);
    AddGameObject(player_hp_ui);
    AddGameObject(player_exp_ui);
    AddGameObject(new Staircase(*this, sf::Vector2f(45 / 2 * 32, 5 * 32), "Title"));
    AddGameObject(new ExampleObject(*this, *playerManager_, sf::Vector2f(0.0f, -100.0f)));
    game_->GetCamera().SetViewCenter(view_main, sf::Vector2f(0, 0));
}

void SceneGame::Update(float delta_time)
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

void SceneGame::Draw(Camera& camera) const
{
    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
    gom_.DelayedDraw(camera); //draw things after Regular draw is finished, helpful for UI or things that should always be drawn last
}

void SceneGame::AddGameObject(GameObject* gameObject)
{
    gom_.Add(gameObject); //add gameobject to the list of gameobjects
}

GameObject* SceneGame::FindGameObject(const std::string& string, const bool byName, const bool byTag, const bool byID)
{//if byTag and byID are both left to default (false), search by name
    return gom_.Find(string, byName, byTag, byID); //returns a GameObject, returns a nullptr if the GameObject is not found
}

void SceneGame::ChangeScene(const std::string& sceneName)
{
    // game_->ChangeScene(sceneName);
    sceneName_ = sceneName;
    changeSceneFlag_ = true;
}

void SceneGame::End()
{
    gom_.Clear();
}
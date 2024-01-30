#include "SceneTitle.h"
#include "LP.h"
#include "ID.h"
#include "Player.h"
#include "ExampleObject.h"
#include "Staircase.h"

SceneTitle::SceneTitle(Game* game) : game_{game}
{}

SceneTitle::~SceneTitle()
{}

void SceneTitle::Init()
{
    mt_ = new MapTitle(game_->GetLP());

    //AddGameObject(new Object(position, &pm_, this)); Example
    AddGameObject(new Player(*this, game_->GetCamera(), *mt_, sf::Vector2f(45 / 2 * 32, 25 / 2 * 32)));
    AddGameObject(new ExampleObject(*this, sf::Vector2f((40 / 2 - 1) * 32, 25 / 2 * 32)));
    AddGameObject(new ExampleObject(*this, sf::Vector2f(50 / 2 * 32, 25 / 2 * 32)));
    AddGameObject(new ExampleObject(*this, sf::Vector2f(45 / 2 * 32, (20 / 2 - 1) * 32)));
    AddGameObject(new ExampleObject(*this, sf::Vector2f(45 / 2 * 32, 30 / 2 * 32)));
    AddGameObject(new Staircase(*this, sf::Vector2f(45 / 2 * 32, 5 * 32), "Game"));
    game_->GetCamera().SetViewCenter(view_main, sf::Vector2f(0, 0));
}

void SceneTitle::Update(float delta_time)
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

void SceneTitle::Draw(Camera& camera) const
{
    mt_->Draw(camera);
    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
    gom_.DelayedDraw(camera); //draw things after Regular draw is finished, helpful for UI or things that should always be drawn last
}

void SceneTitle::AddGameObject(GameObject* gameObject)
{
    gom_.Add(gameObject); //add gameobject to the list of gameobjects
}

GameObject* SceneTitle::FindGameObject(const std::string& string, const bool byName, const bool byTag, const bool byID)
{//if byTag and byID are both left to default (false), search by name
    return gom_.Find(string, byName, byTag, byID); //returns a GameObject, returns a nullptr if the GameObject is not found
}

void SceneTitle::ChangeScene(const std::string& sceneName)
{
    // game_->ChangeScene(sceneName);
    sceneName_ = sceneName;
    changeSceneFlag_ = true;
}

void SceneTitle::End()
{
    gom_.Clear();
    delete(mt_);
}
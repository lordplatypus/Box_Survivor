#include "SceneTitle.h"
#include "LP.h"
#include "ID.h"
#include "Player.h"
#include "UIHP.h"
#include "UIExp.h"
#include "ExampleObject.h"
#include "Staircase.h"

SceneTitle::SceneTitle(Game* game) : game_{game}
{}

SceneTitle::~SceneTitle()
{}

void SceneTitle::Init()
{
    game_->GetPlayerStats().Reset(); // Reset player stats for next run

    mt_ = new MapTitle(game_->GetLP());

    Player* player = new Player(*this, game_->GetCamera(), *mt_, game_->GetPlayerStats(), sf::Vector2f(45 / 2 * 32, 25 / 2 * 32));

    AddGameObject(player);
    AddGameObject(new Staircase(*this, sf::Vector2f(45 / 2 * 32, 7 * 32), "Floor1"));
    game_->GetCamera().SetViewCenter(view_main, sf::Vector2f(0, 0));

    // Text
    titleText_ = game_->GetLP().SetText(main_font, "BOX SURVIVOR", sf::Vector2f(45 / 2 * 32 + 16, 3 * 32), 64);
    game_->GetLP().SetTextOriginCenter(titleText_);
    startText_ = game_->GetLP().SetText(main_font, "Start Game");
    game_->GetLP().SetTextOriginCenter(startText_);
    startText_.setPosition(sf::Vector2f(45 / 2 * 32 + 16, 6 * 32));
    instructionText_ = game_->GetLP().SetText(main_font, "+Movement - 'WASD'\n+Aim - Mouse\n+Shoot - Left Click\n+Cyan square is staircase to next floor\n+Must complete challenge before staircase\n  is unlocked\n+Press 'ESC' to close the game", sf::Vector2f(64, 32 * 16));
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

    camera.Draw(titleText_, layer_main);
    camera.Draw(startText_, layer_main);
    camera.Draw(instructionText_, layer_main);

    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
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
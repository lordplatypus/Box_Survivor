#include "SceneUpgrade.h"
#include "ID.h"
#include "UpgradeManager.h"

SceneUpgrade::SceneUpgrade(Game* game) : game_{game}
{}

SceneUpgrade::~SceneUpgrade()
{}

void SceneUpgrade::Init()
{
    AddGameObject(new UpgradeManager(*this, game_->GetPreviousScene(), game_->GetLP(), game_->GetPlayerStats()));
}

void SceneUpgrade::Update(float delta_time)
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

void SceneUpgrade::Draw(Camera& camera) const
{
    gom_.Draw(camera); //Regular draw - Draw GameObjects in order based on position in the list
}

void SceneUpgrade::AddGameObject(GameObject* gameObject)
{
    gom_.Add(gameObject); //add gameobject to the list of gameobjects
}

GameObject* SceneUpgrade::FindGameObject(const std::string& string, const bool byName, const bool byTag, const bool byID)
{//if byTag and byID are both left to default (false), search by name
    return gom_.Find(string, byName, byTag, byID); //returns a GameObject, returns a nullptr if the GameObject is not found
}

void SceneUpgrade::ChangeScene(const std::string& sceneName)
{
    // game_->ChangeScene(sceneName);
    sceneName_ = sceneName;
    changeSceneFlag_ = true;
}

void SceneUpgrade::End()
{
    gom_.Clear();
}
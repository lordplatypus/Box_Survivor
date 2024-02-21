#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"
#include "ID.h"
#include "SceneNull.h"
#include "SceneTitle.h"
#include "SceneFloor1.h"

static SceneNull nullScene;

Game::Game(Camera& camera) : scene_{&nullScene}
{
    //Set camera
    camera_ = &camera;
    //Load textures
    LP_.Load();
    //Load music
    MP_.Load();
    //Set player stats
    ps_.Reset();
    //Add scenes
    AddScene("Title", new SceneTitle(this));
    AddScene("Floor1", new SceneFloor1(this));
    //Set starting scene
    scene_ = scenes_["Title"];
    scene_->Init();
}

Game::~Game()
{
    Clear();
}

void Game::Update(float delta_time)
{
    scene_->Update(delta_time);
}

void Game::Draw(Camera& camera)
{
    scene_->Draw(camera);
}

void Game::AddScene(const std::string& name, Scene* scene)
{
    scenes_[name] = scene;
}

void Game::ChangeScene(const std::string& newScene)
{
    EndScene();
    scene_ = scenes_[newScene];
    scene_->Init();
}

void Game::EndScene()
{
    scene_->End();
    scene_ = &nullScene;
}

LP& Game::GetLP()
{
    return LP_;
}

MP& Game::GetMP()
{
    return MP_;
}

Camera& Game::GetCamera()
{
    return *camera_;
}

PlayerStats& Game::GetPlayerStats()
{
    return ps_;
}

void Game::Clear()
{
    scene_->End();

    for (auto pair : scenes_)
    {
        delete pair.second;
    }
    scenes_.clear();
}
#include "Staircase.h"
#include "ID.h"

Staircase::Staircase(Scene& scene, const sf::Vector2f& position, const std::string& sceneName)
{
    scene_ = &scene;
    sceneName_ = sceneName;
    name_ = "Staircase";
    tag_ = "Object";
    position_ = position;
    layerID_ = layer_main;
    ID_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;

    // sf::RectangleShape test(sf::Vector2f(imageWidth_, imageHeight_));
    // // rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    // rect_ = test;
    // rect_ = sf::RectangleShape(sf::Vector2f(16, 16));
    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(0, 255, 255, 255));
    rect_.setPosition(position_);

    //Sprite set up
    //sprite_ = LP.SetSprite(pic_texture, position_);
}

Staircase::~Staircase()
{}

void Staircase::Update(float delta_time)
{}

void Staircase::Draw(Camera& camera) const
{
    //Draw sprite to layer
    camera.Draw(rect_, layer_main);
}

void Staircase::DelayedDraw(Camera& camera) const
{
    //same as Draw
    //this function will be called after Draw
    //Good for things that need to be drawn last - UI
}

void Staircase::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (!GetLock() && other.GetName() == "Player")
    {
        //EX: if the collided object is "Staircase" then do this
        scene_->ChangeScene(sceneName_);
    }
}

void Staircase::SetLock(bool lock)
{
    lock_ = lock;
}

bool Staircase::GetLock() const
{
    return lock_;
}
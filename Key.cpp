#include "Key.h"
#include "ID.h"

Key::Key(ChallengeKeys& challenge, const sf::Vector2f& position, const int id)
{
    challenge_ = &challenge;
    name_ = "Key";
    tag_ = "Object";
    position_ = position;
    layerID_ = layer_main;
    ID_ = id;
    imageWidth_ = 32;
    imageHeight_ = 32;

    // sf::RectangleShape test(sf::Vector2f(imageWidth_, imageHeight_));
    // // rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    // rect_ = test;
    // rect_ = sf::RectangleShape(sf::Vector2f(16, 16));
    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color::Yellow);
    rect_.setPosition(position_);

    //Sprite set up
    //sprite_ = LP.SetSprite(pic_texture, position_);
}

Key::~Key()
{}

void Key::Update(float delta_time)
{}

void Key::Draw(Camera& camera) const
{
    //Draw sprite to layer
    //camera.Draw(sprite_, layer_main);
    camera.Draw(rect_, layer_main);
}

void Key::DelayedDraw(Camera& camera) const
{
    //same as Draw
    //this function will be called after Draw
    //Good for things that need to be drawn last - UI
}

void Key::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (other.GetName() == "Player")
    {
        if (challenge_ != nullptr)
        {
            challenge_->KeyCollected();
            Kill();
        }
    }
}
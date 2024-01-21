#include "ExampleObject.h"
#include "ID.h"

ExampleObject::ExampleObject(Scene& scene, const sf::Vector2f& position)
{
    scene_ = &scene;
    name_ = "ExampleObject";
    tag_ = "Example";
    position_ = position;
    velocity_ = sf::Vector2f(500.0f, 500.0f);
    layerID_ = layer_main;
    ID_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;

    // sf::RectangleShape test(sf::Vector2f(imageWidth_, imageHeight_));
    // // rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    // rect_ = test;
    // rect_ = sf::RectangleShape(sf::Vector2f(16, 16));
    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(255, 255, 255, 255));
    rect_.setPosition(position_);

    //Sprite set up
    //sprite_ = LP.SetSprite(pic_texture, position_);
}

ExampleObject::~ExampleObject()
{}

void ExampleObject::Update(float delta_time)
{
    //Calculations go here
    InputHandle(delta_time);
}

void ExampleObject::InputHandle(float delta_time)
{
    if (IP_.GetButton(sf::Keyboard::W))
    {
        position_.y -= velocity_.y * delta_time;
    }
    if (IP_.GetButton(sf::Keyboard::A))
    {
        position_.x -= velocity_.x * delta_time;
    }
    if (IP_.GetButton(sf::Keyboard::S))
    {
        position_.y += velocity_.y * delta_time;
    }
    if (IP_.GetButton(sf::Keyboard::D))
    {
        position_.x += velocity_.x * delta_time;
    }
    rect_.setPosition(position_);

    IP_.Update();
}

void ExampleObject::Draw(Camera& camera) const
{
    //Draw sprite to layer
    //camera.Draw(sprite_, layer_main);
    camera.Draw(rect_, layer_main);
}

void ExampleObject::DelayedDraw(Camera& camera) const
{
    //same as Draw
    //this function will be called after Draw
    //Good for things that need to be drawn last - UI
}

void ExampleObject::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (other.GetName() == "Player")
    {
        //EX: if the collided object is "player" then do this
    }
}
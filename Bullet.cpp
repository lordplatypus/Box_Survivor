#include "Bullet.h"
#include "ID.h"

Bullet::Bullet(Map& map, const std::string& name, const sf::Vector2f& position, const sf::Vector2f velocity, const float lifespan)
{
    map_ = &map;
    name_ = name;
    tag_ = "Bullet";
    position_ = position;
    velocity_ = velocity;
    layerID_ = layer_main;
    ID_ = 0;
    imageWidth_ = 8;
    imageHeight_ = 8;
    lifespan_ = lifespan;

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(255, 255, 255, 255));
    rect_.setPosition(position_);
}

Bullet::~Bullet()
{}

void Bullet::Update(float delta_time)
{
    //Calculations go here
    // position_.x += velocity_.x * delta_time;
    // position_.y += velocity_.y * delta_time;
    position_ += velocity_ * delta_time;
    life_ += delta_time;
    if (!map_->Transversable(position_) || life_ >= lifespan_) Kill();
    rect_.setPosition(position_);
}

void Bullet::Draw(Camera& camera) const
{
    //Draw sprite to layer
    //camera.Draw(sprite_, layer_main);
    camera.Draw(rect_, layer_main);
}

void Bullet::DelayedDraw(Camera& camera) const
{
    //same as Draw
    //this function will be called after Draw
    //Good for things that need to be drawn last - UI
}

void Bullet::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (other.GetName() != "Staircase")
    {
        Kill();
    }
}
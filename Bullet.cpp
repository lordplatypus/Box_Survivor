#include "Bullet.h"
#include "ID.h"

Bullet::Bullet(Map& map, const sf::Vector2f& position, const sf::Vector2f velocity, const float lifespan)
{
    map_ = &map;
    name_ = "Player_Bullet";
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
    position_ += velocity_ * delta_time;
    life_ += delta_time;
    if (!map_->Transversable(position_) || life_ >= lifespan_) Kill();
    rect_.setPosition(position_);
}

void Bullet::Draw(Camera& camera) const
{
    camera.Draw(rect_, layer_main);
}

void Bullet::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (other.GetName() != "Player" && other.GetTag() != "Object" && other.GetName() != "Ghost" && other.GetName() != "Bullet")
    {
        Kill();
    }
}
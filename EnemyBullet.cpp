#include "EnemyBullet.h"
#include "ID.h"

EnemyBullet::EnemyBullet(PlayerManager& playerManager, Map& map, const sf::Vector2f& position, const sf::Vector2f velocity, const float lifespan, const sf::Color& color, int damage)
{
    playerManager_ = &playerManager;
    map_ = &map;
    name_ = "Bullet";
    tag_ = "Enemy";
    position_ = position;
    velocity_ = velocity;
    layerID_ = layer_main;
    ID_ = 0;
    imageWidth_ = 8;
    imageHeight_ = 8;
    lifespan_ = lifespan;
    damage_ = damage;

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(color);
    rect_.setPosition(position_);
}

EnemyBullet::~EnemyBullet()
{}

void EnemyBullet::Update(float delta_time)
{
    position_ += velocity_ * delta_time;
    life_ += delta_time;
    if (!map_->Transversable(position_) || life_ >= lifespan_) Kill();
    rect_.setPosition(position_);
}

void EnemyBullet::Draw(Camera& camera) const
{
    camera.Draw(rect_, layer_main);
}

void EnemyBullet::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (other.GetName() != "Staircase" && other.GetTag() != "Enemy")
    {
        if (other.GetName() == "Player") playerManager_->DealDamage(damage_);
        Kill();
    }
}
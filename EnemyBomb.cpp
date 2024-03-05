#include "EnemyBomb.h"
#include "ID.h"
#include "GameOver.h"

EnemyBomb::EnemyBomb(PlayerManager& playerManager, const sf::Vector2f& position, const sf::Vector2i size, float lifespan)
{
    playerManager_ = &playerManager;
    name_ = "Bomb";
    tag_ = "Enemy";
    ID_ = 0;
    layerID_ = layer_main;
    imageWidth_ = size.x;
    imageHeight_ = size.y;
    SetLeft(-imageWidth_/2);
    SetTop(-imageWidth_/2);
    SetRight(imageWidth_/2);
    SetBottom(imageWidth_/2);
    position_ = position;
    attackPower_ = 1;
    lifespan_ = lifespan;
    SetActive(false);

    outline_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    outline_.setFillColor(sf::Color::Transparent);
    outline_.setOutlineColor(sf::Color(255, 255, 0, 255));
    outline_.setOutlineThickness(4.0f);
    outline_.setOrigin(sf::Vector2f(imageWidth_/2, imageHeight_/2));
    outline_.setPosition(position_);

    fill_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    fill_.setFillColor(sf::Color(255, 255, 0, 255));
    fill_.setOrigin(sf::Vector2f(imageWidth_/2, imageHeight_/2));
    fill_.setPosition(position_);
    fill_.setScale(sf::Vector2f(0, 0));
}

void EnemyBomb::Update(float delta_time)
{
    life_ += delta_time;
    if (life_ >= lifespan_) 
    {
        SetActive(true);
        fill_.setFillColor(sf::Color(255, 0, 0, 255));
        damageTime_ += delta_time;
        if (damageTime_ >= damageLifespan_) Kill();
    }
    else fill_.setScale(sf::Vector2f(life_ / lifespan_, life_ / lifespan_));
}

void EnemyBomb::Draw(Camera& camera) const
{
    camera.Draw(outline_, layerID_);
    camera.Draw(fill_, layerID_);
}

void EnemyBomb::ReactOnCollision(GameObject& other)
{
    if (other.GetName() == "Player")
    {
        playerManager_->DealDamage(1);
    }
}

void EnemyBomb::Kill()
{
    isDead_ = true;
}
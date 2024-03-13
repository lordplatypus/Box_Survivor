#include "EnemyGhost.h"
#include "ID.h"

EnemyGhost::EnemyGhost(PlayerManager& playerManager, int id, const sf::Vector2f& position)
{
    playerManager_ = &playerManager;
    name_ = "Ghost";
    tag_ = "Enemy";
    ID_ = 0;
    layerID_ = layer_main;
    imageWidth_ = 32 * 2;
    imageHeight_ = 32 * 2;
    position_ = position;
    attackPower_ = 1;
    velocity_ = sf::Vector2f(200, 200);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(255, 255, 255, 126));
    rect_.setPosition(position_);
}

void EnemyGhost::Update(float delta_time)
{
    sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
    sf::Vector2f normal = Normalize(sf::Vector2f(playerPosition.x - position_.x, playerPosition.y - position_.y));
    sf::Vector2f moveTo(position_.x + (normal.x * velocity_.x * delta_time), position_.y + (normal.y * velocity_.y * delta_time));
    position_ = moveTo;
    rect_.setPosition(position_);
}

void EnemyGhost::Draw(Camera& camera) const
{
    camera.Draw(rect_, layerID_);
}

void EnemyGhost::ReactOnCollision(GameObject& other)
{
    if (other.GetName() == "Player")
    {
        playerManager_->DealDamage(1);
    }
}

void EnemyGhost::Kill()
{
    isDead_ = true;
}
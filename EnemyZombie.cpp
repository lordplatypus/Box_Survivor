#include "EnemyZombie.h"

EnemyZombie::EnemyZombie(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position)
{
    Init(&dungeonScene, &map, &playerManager, "Zombie", id, sf::Vector2i(32, 32), position, 320, 1, 1, 100);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(255, 0, 0, 255));
    rect_.setPosition(position_);
}

EnemyZombie::~EnemyZombie()
{}

void EnemyZombie::Update(float delta_time)
{
    if (seePlayerFlag_)
    {
        sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
        sf::Vector2f normal = Normalize(sf::Vector2f(playerPosition.x - position_.x, playerPosition.y - position_.y));
        sf::Vector2f moveTo(position_.x + (normal.x * velocity_.x * delta_time), position_.y + (normal.y * velocity_.y * delta_time));
        if (Transversable(moveTo))
        {
            position_ = moveTo;
            rect_.setPosition(position_);
        }    
    }
    else if (SeePlayer())
    {
        seePlayerFlag_ = true;
    }
}

void EnemyZombie::Draw(Camera& camera) const
{
    camera.Draw(rect_, layerID_);
}

void EnemyZombie::ReactOnCollision(GameObject& other)
{
    if (other.GetName() == "Player")
    {
        playerManager_->DealDamage(1);
        Kill();
    }
    else if (other.GetName() == "Player_Bullet")
    {
        playerManager_->AddExperience(1);
        Kill();
    }
}
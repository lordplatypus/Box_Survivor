#include "EnemySlime.h"

EnemySlime::EnemySlime(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position, const sf::Vector2f& size)
{
    Init(&dungeonScene, &map, &playerManager, "Slime", id, sf::Vector2i(size.x, size.y), position, 320, 1, 1, 32 / size.x * 100);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(0, 0, 255, 255));
    rect_.setPosition(position_);
}

EnemySlime::~EnemySlime()
{}

void EnemySlime::Update(float delta_time)
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

void EnemySlime::Draw(Camera& camera) const
{
    camera.Draw(rect_, layerID_);
}

void EnemySlime::ReactOnCollision(GameObject& other)
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

void EnemySlime::Kill()
{
    isDead_ = true;
    dungeonScene_->SetEnemyCount(dungeonScene_->GetEnemyCount() - 1);

    if (imageWidth_ > 16) 
    {
        int slimesToPlace = 2;
        int failsafe = 100;
        while (slimesToPlace > 0 && failsafe > 0)
        {
            failsafe--;
            int randX = 1 - std::rand() / ((RAND_MAX + 1u) / 3);
            int randY = 1 - std::rand() / ((RAND_MAX + 1u) / 3);
            sf::Vector2f slimePosition(position_.x + (randX * 32), position_.y + (randY * 32));
            if (Transversable(slimePosition))
            {
                slimesToPlace--;
                dungeonScene_->AddGameObject(new EnemySlime(*dungeonScene_, *map_, *playerManager_, ID_, slimePosition, sf::Vector2f(imageWidth_-8, imageHeight_-8)));
            }
        }
    }
}
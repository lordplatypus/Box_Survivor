#include "EnemyNinja.h"
#include "Math.h"

EnemyNinja::EnemyNinja(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position)
{
    Init(&dungeonScene, &map, &playerManager, "Ninja", id, sf::Vector2i(32, 32), position, 32*12, 2, 1, 250, 3);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(255, 0, 255, 50));
    rect_.setPosition(position_);
}

void EnemyNinja::Update(float delta_time)
{
    if (teleportFlag_)
    {
        teleportFlag_ = false;
        waitTimer_ = 0.0f;
        rect_.setFillColor(sf::Color(255, 0, 255, 255));
        sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
        sf::Vector2f playerCenter(playerPosition.x + 16, playerPosition.y + 16);
        float randomAngle = std::rand() / ((RAND_MAX + 1u) / 360);
        randomAngle = Math::DegToRad(randomAngle);
        sf::Vector2f moveTo(playerCenter.x + cos(randomAngle) * 80, playerCenter.y + sin(randomAngle) * 80);
        if (Transversable(moveTo))
        {
            position_ = moveTo;
            rect_.setPosition(position_);
            hpBar_->SetPosition(sf::Vector2f(position_.x + imageWidth_ / 2, position_.y - imageHeight_ / 2));
        } 
    }
    else if (waitTimer_ < waitTime_)
    {
        waitTimer_ += delta_time;
    }
    else if (seePlayerFlag_)
    {
        sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
        sf::Vector2f normal = Normalize(sf::Vector2f(playerPosition.x - position_.x, playerPosition.y - position_.y));
        sf::Vector2f moveTo(position_.x + (normal.x * velocity_.x * delta_time), position_.y + (normal.y * velocity_.y * delta_time));
        if (Transversable(moveTo))
        {
            position_ = moveTo;
            rect_.setPosition(position_);
            hpBar_->SetPosition(sf::Vector2f(position_.x + imageWidth_ / 2, position_.y - imageHeight_ / 2));
        }    
    }
    else if (SeePlayer())
    {
        seePlayerFlag_ = true;
        teleportFlag_ = true;
    }
}

void EnemyNinja::Draw(Camera& camera) const
{
    camera.Draw(rect_, layerID_);
    hpBar_->Draw(camera);
}

void EnemyNinja::ReactOnCollision(GameObject& other)
{
    if (other.GetName() == "Player")
    {
        playerManager_->DealDamage(1);
        Kill();
    }
    else if (other.GetName() == "Player_Bullet" && !other.IsDead())
    {
        TakeDamage();
        teleportFlag_ = true;
    }
}
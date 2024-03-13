#include "EnemyShooter.h"
#include "EnemyBullet.h"
#include <cmath>

EnemyShooter::EnemyShooter(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position)
{
    Init(&dungeonScene, &map, &playerManager, "Shooter", id, sf::Vector2i(32, 32), position, 320, 3, 1, 250, 2);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(0, 255, 0, 255));
    rect_.setPosition(position_);
}

void EnemyShooter::Update(float delta_time)
{
    if (seePlayerFlag_)
    {
        sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
        float distance = sqrt(pow(playerPosition.x - position_.x, 2) + pow(playerPosition.y - position_.y, 2));
        sf::Vector2f normal = Normalize(sf::Vector2f(playerPosition.x - position_.x, playerPosition.y - position_.y));
        sf::Vector2f moveTo(position_.x + (normal.x * velocity_.x * delta_time), position_.y + (normal.y * velocity_.y * delta_time));
        if (abs(distance) < 10 * 32) moveTo = sf::Vector2f(position_.x - (normal.x * velocity_.x * delta_time), position_.y - (normal.y * velocity_.y * delta_time));
        if (Transversable(moveTo))
        {
            position_ = moveTo;
            rect_.setPosition(position_);
            hpBar_->SetPosition(sf::Vector2f(position_.x + imageWidth_ / 2, position_.y - imageHeight_ / 2));
        }

        shootTimer_ += delta_time;
        if (shootTimer_ >= shootTime_)
        {
            shootTimer_ = 0.0f;
            sf::Vector2f startPos = sf::Vector2f(position_.x + imageWidth_/2 + normal.x * imageWidth_, position_.y + imageHeight_/2 + normal.y * imageHeight_);
            sf::Vector2f bulletVelocity = normal * 400.0f;
            dungeonScene_->AddGameObject(new EnemyBullet(*playerManager_, *map_, startPos, bulletVelocity, 1.0f, sf::Color::Green, attackPower_));
        }
    }
    else if (SeePlayer())
    {
        seePlayerFlag_ = true;
    }
}

void EnemyShooter::Draw(Camera& camera) const
{
    camera.Draw(rect_, layerID_);
    hpBar_->Draw(camera);
}

void EnemyShooter::MovementHandle(float delta_time)
{
    
}

void EnemyShooter::ShootingHandle(float delta_time)
{
    
}

void EnemyShooter::ReactOnCollision(GameObject& other)
{
    if (other.GetName() == "Player")
    {
        playerManager_->DealDamage(1);
        Kill();
    }
    else if (other.GetName() == "Player_Bullet" && !other.IsDead())
    {
        TakeDamage();
    }
}
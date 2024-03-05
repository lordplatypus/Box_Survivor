#include "Enemy.h"
#include "ID.h"
#include <cmath>

Enemy::~Enemy()
{
    delete(hpBar_);
}

void Enemy::Init(SceneDungeon* dungeonScene, Map* map, PlayerManager* playerManager, const std::string& name, int id, const sf::Vector2i& size, 
                 const sf::Vector2f& position, int perceptionRange, int maxHP, int attackPower, float speed, int exp)
{
    dungeonScene_ = dungeonScene;
    map_ = map;
    playerManager_ = playerManager;
    name_ = name;
    tag_ = "Enemy";
    ID_ = id;
    layerID_ = layer_main;
    imageWidth_ = size.x;
    imageHeight_ = size.y;
    position_ = position;
    perceptionRange_ = perceptionRange;
    maxHP_ = maxHP;
    HP_ = maxHP;
    attackPower_ = attackPower;
    velocity_ = sf::Vector2f(speed, speed);
    exp_ = exp;

    hpBar_ = new HPBar(sf::Vector2f(position_.x + imageWidth_ / 2, position_.y - imageHeight_ / 2), sf::Vector2i(imageWidth_, imageHeight_ / 4), 1.0f);
}

bool Enemy::SeePlayer() const
{
    return GetPerceptionArea().intersects(playerManager_->GetPlayer()->GetHitBox());
}

bool Enemy::Transversable(const sf::Vector2f& position) const
{
    if (!map_->Transversable(position)) return false;
    if (!map_->Transversable(sf::Vector2f(position.x, position.y + imageHeight_))) return false;
    if (!map_->Transversable(sf::Vector2f(position.x + imageWidth_, position.y))) return false;
    if (!map_->Transversable(sf::Vector2f(position.x + imageWidth_, position.y + imageHeight_))) return false;
    return true;
}

sf::IntRect Enemy::GetPerceptionArea() const
{
    return sf::IntRect(position_.x - perceptionRange_, position_.y - perceptionRange_, perceptionRange_ * 2 + imageWidth_, perceptionRange_ * 2 + imageHeight_);
}

sf::Vector2f Enemy::Normalize(const sf::Vector2f& vector)
{
    float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    if (length != 0) return sf::Vector2f(vector.x / length, vector.y / length);
    return vector;
}

void Enemy::TakeDamage()
{
    HP_ -= playerManager_->GetPlayerStats()->GetDamage();
    hpBar_->SetPercentage((float)HP_ / (float)maxHP_);
    if (HP_ <= 0)
    {
        playerManager_->AddExperience(exp_);
        Kill();
    }
}

void Enemy::Kill()
{
    isDead_ = true;
    dungeonScene_->SetEnemyCount(dungeonScene_->GetEnemyCount() - 1);
}
#ifndef ENEMY_LASER_H_
#define ENEMY_LASER_H_
#include "Enemy.h"

class EnemyLaser : public Enemy
{
public:
    EnemyLaser(PlayerManager& playerManager, const sf::Vector2f& position, const sf::Vector2i size, float lifespan);
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    virtual void Kill() override;

private:
    void ReactOnCollision(GameObject& other) override;

private:
    float lifespan_{0.0f};
    float life_{0.0f};
    float damageLifespan_{1.0f};
    float damageTime_{0.0f};
    sf::RectangleShape outline_;
    sf::RectangleShape fill_;
};

#endif
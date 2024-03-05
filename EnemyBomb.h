#ifndef ENEMY_BOMB_H_
#define ENEMY_BOMB_H_
#include "Enemy.h"

class EnemyBomb : public Enemy
{
public:
    EnemyBomb(PlayerManager& playerManager, const sf::Vector2f& position, const sf::Vector2i size, float lifespan);
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    virtual void Kill() override;

private:
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    float lifespan_{0.0f};
    float life_{0.0f};

    float damageLifespan_{0.1f};
    float damageTime_{0.0f};

    sf::RectangleShape outline_;
    sf::RectangleShape fill_;
};

#endif
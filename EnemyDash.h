#ifndef ENEMY_DASH_H_
#define ENEMY_DASH_H_
#include "Enemy.h"

class EnemyDash : public Enemy
{
public:
    EnemyDash(const sf::Vector2f& position, const sf::Vector2f& destination, int thickness, float lifespan);
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    virtual void Kill() override;

private:
    sf::Vector2f destination_;
    float lifespan_{0.0f};
    float life_{0.0f};
    sf::RectangleShape outline_;
    sf::RectangleShape fill_;
};

#endif
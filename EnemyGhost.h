#ifndef ENEMY_GHOST_H_
#define ENEMY_GHOST_H_
#include "Enemy.h"

class EnemyGhost : public Enemy
{
public:
    EnemyGhost(PlayerManager& playerManager, int id, const sf::Vector2f& position);
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    virtual void Kill() override;

private:
    void ReactOnCollision(GameObject& other) override;

private:
    sf::RectangleShape rect_;
};

#endif
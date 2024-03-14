#ifndef ENEMY_NINJA_H_
#define ENEMY_NINJA_H_
#include "Enemy.h"

class EnemyNinja : public Enemy
{
public:
    EnemyNinja(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position);
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    void ReactOnCollision(GameObject& other) override;

private:
    sf::RectangleShape rect_;
    bool teleportFlag_{false};
    float waitTime_{0.5f};
    float waitTimer_{0.0f};
};

#endif
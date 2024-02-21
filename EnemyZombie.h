#ifndef ENEMY_ZOMBIE_H_
#define ENEMY_ZOMBIE_H_
#include "Enemy.h"

class EnemyZombie : public Enemy
{
public:
    EnemyZombie(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position);
    ~EnemyZombie() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    sf::RectangleShape rect_;
};

#endif
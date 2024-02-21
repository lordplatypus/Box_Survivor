#ifndef ENEMY_SHOOTER_H_
#define ENEMY_SHOOTER_H_
#include "Enemy.h"

class EnemyShooter : public Enemy
{
public:
    EnemyShooter(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position);
    ~EnemyShooter() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    void MovementHandle(float delta_time);
    void ShootingHandle(float delta_time);
    void ReactOnCollision(GameObject& other) override;

private:
    sf::RectangleShape rect_;
    float shootTime_{3.0f};
    float shootTimer_{3.0f};
};

#endif
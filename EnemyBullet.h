#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_
#include "GameObject.h"
#include "Map.h"
#include "PlayerManager.h"

class EnemyBullet : public GameObject
{
public:
    EnemyBullet(PlayerManager& playerManager, Map& map, const sf::Vector2f& position, const sf::Vector2f velocity, const float lifespan, const sf::Color& color, int damage);
    ~EnemyBullet() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    void ReactOnCollision(GameObject& other) override;

private:
    PlayerManager* playerManager_{nullptr};
    Map* map_{nullptr};
    sf::RectangleShape rect_;
    float lifespan_{0.0f};
    float life_{0.0f};
    int damage_{0};
};

#endif
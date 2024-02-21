#ifndef ENEMY_SLIME_H_
#define ENEMY_SLIME_H_
#include "Enemy.h"

class EnemySlime : public Enemy
{
public:
    EnemySlime(SceneDungeon& dungeonScene, Map& map, PlayerManager& playerManager, int id, const sf::Vector2f& position, const sf::Vector2f& size);
    ~EnemySlime() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    virtual void Kill() override;

private:
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    sf::RectangleShape rect_;
};

#endif
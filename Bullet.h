#ifndef BULLET_H_
#define BULLET_H_
#include "GameObject.h"
#include "LP.h"
#include "IP.h"
#include "Map.h"

class Bullet : public GameObject
{
public:
    Bullet(Map& map, const std::string& name, const sf::Vector2f& position, const sf::Vector2f velocity, const float lifespan);
    ~Bullet() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    void DelayedDraw(Camera& camera) const override;

private:
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    Map* map_;
    sf::RectangleShape rect_;
    float lifespan_{0.0f};
    float life_{0.0f};
};

#endif
#ifndef EXAMPLE_OBJECT_H_
#define EXAMPLE_OBJECT_H_
#include "GameObject.h"
#include "PlayerManager.h"

class ExampleObject : public GameObject
{
public:
    ExampleObject(Scene& scene, PlayerManager& player_manager, const sf::Vector2f& position);
    ~ExampleObject() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    void DelayedDraw(Camera& camera) const override;

private:
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    PlayerManager* player_manager_{nullptr};
    sf::RectangleShape rect_;
};

#endif
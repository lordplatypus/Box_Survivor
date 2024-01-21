#ifndef EXAMPLE_OBJECT_H_
#define EXAMPLE_OBJECT_H_
#include "GameObject.h"
#include "LP.h"
#include "IP.h"

class ExampleObject : public GameObject
{
public:
    ExampleObject(Scene& scene, const sf::Vector2f& position);
    ~ExampleObject() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    void DelayedDraw(Camera& camera) const override;

private:
    void InputHandle(float delta_time);
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    IP IP_;
    sf::RectangleShape rect_;
    const float speed{100.0f};
};

#endif
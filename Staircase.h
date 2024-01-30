#ifndef STAIRCASE_H_
#define STAIRCASE_H_
#include "GameObject.h"
#include "LP.h"
#include "IP.h"

class Staircase : public GameObject
{
public:
    Staircase(Scene& scene, const sf::Vector2f& position, const std::string& sceneName);
    ~Staircase() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    void DelayedDraw(Camera& camera) const override;

private:
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    sf::RectangleShape rect_;
    std::string sceneName_;
};

#endif
#ifndef PLAYER_H_
#define PLAYER_H_
#include "GameObject.h"
#include "LP.h"
#include "IP.h"
#include "Map.h"
#include "PlayerStats.h"

class Player : public GameObject
{
public:
    Player(Scene& scene, Camera& camera, Map& map, PlayerStats& ps, const sf::Vector2f& position);
    ~Player() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    void DelayedDraw(Camera& camera) const override;

private:
    void InputHandle(float delta_time);
    bool Transversable(const sf::Vector2f& position) const;
    //Collision / Perception
    void ReactOnCollision(GameObject& other) override;

private:
    Camera* camera_{nullptr};
    IP IP_;
    sf::RectangleShape rect_;
    const float speed{100.0f};
    Map* map_{nullptr};
    PlayerStats* ps_{nullptr};
};

#endif
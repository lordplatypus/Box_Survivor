#ifndef GAME_OVER_H_
#define GAME_OVER_H_
#include "GameObject.h"
#include "LP.h"
#include "IP.h"

class GameOver : public GameObject
{
public:
    GameOver(Scene& scene, LP& LP, const sf::Vector2f& position);
    ~GameOver() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    IP IP_;
    sf::Text text_;
};

#endif
#ifndef KEY_H_
#define KEY_H_
#include "GameObject.h"
#include "ChallengeKeys.h"

class Key : public GameObject
{
public:
    Key(ChallengeKeys& challenge, const sf::Vector2f& position, const int id);
    ~Key() override;
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    void DelayedDraw(Camera& camera) const override;

private:
    void ReactOnCollision(GameObject& other) override;

private:
    ChallengeKeys* challenge_{nullptr};
    sf::RectangleShape rect_;
};

#endif
#ifndef UICHALLENGE_H_
#define UICHALLENGE_H_
#include "GameObject.h"
#include "LP.h"

class UIChallenge : public GameObject
{
public:
    UIChallenge(LP& LP, const sf::Vector2f& position);
    ~UIChallenge() override;
    void Draw(Camera& camera) const override;

    void SetText(const std::string& new_text);

private:
    sf::Text text_;
};

#endif
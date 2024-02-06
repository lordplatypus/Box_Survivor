#ifndef UIEXP_H_
#define UIEXP_H_
#include "GameObject.h"

class UIExp : public GameObject
{
public:
    UIExp(int max_experience, int current_experience, const sf::Vector2f& position);
    ~UIExp() override;
    void Draw(Camera& camera) const override;

    void SetCurrentExperience(const int current_experience);
    void SetMaxExperience(const int max_experience);

private:
    void RenderTexture();

private:
    int max_experience_{0};
    int current_experience_{0};
    sf::RectangleShape outline_;
    sf::RectangleShape bar_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

#endif
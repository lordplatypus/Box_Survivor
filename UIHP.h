#ifndef UIHP_H_
#define UIHP_H_
#include "GameObject.h"

class UIHP : public GameObject
{
public:
    UIHP(int max_hp, int current_hp, const sf::Vector2f& position);
    ~UIHP() override;
    void Draw(Camera& camera) const override;

    void SetCurrentHP(const int hp);
    void SetMaxHP(const int max_hp);

private:
    void RenderTexture();

private:
    int max_hp_{0};
    int current_hp_{0};
    sf::RectangleShape diamond_;
    sf::Texture diamond_texture_;
    sf::Sprite hp_ui_sprite_;
};

#endif
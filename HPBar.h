#ifndef HP_BAR_H_
#define HP_BAR_H_
#include "Camera.h"

class HPBar
{
public:
    HPBar(const sf::Vector2f& position, const sf::Vector2i& size, const float startPercentage, const bool outlineFlag = false);
    ~HPBar();
    void Draw(Camera& camera) const;
    void SetPercentage(const float percentage);
    void SetPosition(const sf::Vector2f& position);

private:
    void RenderTexture();

private:
    float percentage_{0};
    bool outlineFlag_{false};
    sf::Vector2f position_;
    sf::Vector2i size_;
    sf::RectangleShape outline_;
    sf::RectangleShape bar_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

#endif
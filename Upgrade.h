#ifndef UPGRADE_H_
#define UPGRADE_H_
#include "Camera.h"
#include "PlayerStats.h"
#include "LP.h"

class Upgrade
{
public:
    Upgrade();
    virtual ~Upgrade();
    void Init(LP& lp, PlayerStats& playerStats, const sf::Vector2f worldPosition, const std::string& upgradeText);
    void Draw(Camera& camera) const;
private:
    void RenderTexture();
public:
    void Select();
    void UnSelect();

    virtual void Apply();

protected:
    PlayerStats* playerStats_{nullptr};
    sf::Vector2f worldPosition_;
    sf::Vector2f position_;
    int width_{0};
    int height_{0};
    sf::RectangleShape rect_;
    sf::Text text_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

#endif
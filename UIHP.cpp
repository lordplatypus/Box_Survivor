#include <cmath>
#include "UIHP.h"
#include "ID.h"

UIHP::UIHP(int max_hp, int current_hp, const sf::Vector2f& position)
{
    name_ = "UIHP";
    tag_ = "UI";
    position_ = position;
    layerID_ = layer_UI;
    ID_ = 0;
    imageWidth_ = sqrt(pow(32, 2) + pow(32, 2));
    imageHeight_ = imageWidth_;
    max_hp_ = max_hp;
    current_hp_ = current_hp;
    SetActive(false);

    diamond_.setSize(sf::Vector2f(32, 32));
    diamond_.setOrigin(sf::Vector2f(32 / 2, 32 / 2));
    diamond_.setRotation(45);

    RenderTexture();
}

UIHP::~UIHP()
{}

void UIHP::Draw(Camera& camera) const
{
    //Draw sprite to layer
    camera.Draw(hp_ui_sprite_, layerID_);
}

void UIHP::SetCurrentHP(const int hp)
{
    current_hp_ = hp;
    RenderTexture();
}

void UIHP::SetMaxHP(const int max_hp)
{
    max_hp_ = max_hp;
    RenderTexture();
}

void UIHP::RenderTexture()
{
    sf::RenderTexture render_texture;
    render_texture.create(imageWidth_ * max_hp_, imageHeight_);
    render_texture.clear(sf::Color::Transparent);

    for (int i = 0; i < max_hp_; i++)
    {
        diamond_.setPosition(sf::Vector2f(i * imageWidth_ + (imageWidth_ / 2), imageHeight_ / 2));
        if (i <= current_hp_ - 1) diamond_.setFillColor(sf::Color::Red);
        else diamond_.setFillColor(sf::Color(125, 125, 125, 255));
        render_texture.draw(diamond_);
    }

    render_texture.display();
    diamond_texture_ = render_texture.getTexture();
    hp_ui_sprite_ = sf::Sprite(diamond_texture_);
    hp_ui_sprite_.setPosition(position_);
}
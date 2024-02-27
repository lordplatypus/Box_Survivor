#include "Upgrade.h"
#include "ID.h"

Upgrade::Upgrade()
{}

Upgrade::~Upgrade()
{}

void Upgrade::Init(LP& lp, PlayerStats& playerStats, const sf::Vector2f worldPosition, const std::string& upgradeText)
{
    playerStats_ = &playerStats;
    worldPosition_ = worldPosition;
    position_ = worldPosition;

    width_ = 14 * 32;
    height_ = 23 * 32;

    rect_.setPosition(sf::Vector2f(32, 32));
    rect_.setSize(sf::Vector2f(width_ - 64, height_ - 64));
    rect_.setOutlineThickness(32);
    rect_.setOutlineColor(sf::Color(255, 255, 255, 255));
    rect_.setFillColor(sf::Color::Transparent);

    text_ = lp.SetText(main_font, upgradeText, sf::Vector2f(64, 64), 32, sf::Vector2f(0.8f, 0.8f));

    UnSelect();
}

void Upgrade::Draw(Camera& camera) const
{
    camera.Draw(sprite_, layer_UI);
}

void Upgrade::RenderTexture()
{
    sf::RenderTexture render_texture;
    render_texture.create(width_, height_);
    render_texture.clear(sf::Color::Transparent);

    render_texture.draw(rect_);
    render_texture.draw(text_);
    
    render_texture.display();
    texture_ = render_texture.getTexture();
    sprite_ = sf::Sprite(texture_);
    // sprite_.setPosition(position_);
}

void Upgrade::Select()
{
    rect_.setOutlineColor(sf::Color::White);
    text_.setFillColor(sf::Color::White);
    RenderTexture();
    sprite_.setScale(sf::Vector2f(1, 1));
    position_ = worldPosition_;
    sprite_.setPosition(position_);
}

void Upgrade::UnSelect()
{
    rect_.setOutlineColor(sf::Color(128, 128, 128, 255));
    text_.setFillColor(sf::Color(128, 128, 128, 255));
    RenderTexture();
    sprite_.setScale(sf::Vector2f(0.8f, 0.8f));
    sf::FloatRect spriteSize = sprite_.getGlobalBounds();
    position_ = sf::Vector2f(worldPosition_.x + ((width_ - spriteSize.width) / 2), worldPosition_.y + ((height_ - spriteSize.height) / 2));
    sprite_.setPosition(position_);
}

void Upgrade::Apply()
{}
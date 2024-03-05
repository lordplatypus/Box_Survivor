#include "HPBar.h"
#include "ID.h"

HPBar::HPBar(const sf::Vector2f& position, const sf::Vector2i& size, const float startPercentage, const bool outlineFlag)
{
    position_ = position;
    size_ = size;
    percentage_ = startPercentage;
    outlineFlag_ = outlineFlag;

    if (outlineFlag_)
    {
        outline_.setSize(sf::Vector2f(size_.x - 8, size_.y - 8));
        outline_.setFillColor(sf::Color::Transparent);
        outline_.setOutlineColor(sf::Color::White);
        outline_.setOutlineThickness(4);
        outline_.setPosition(sf::Vector2f(4, 4));
    }

    bar_.setSize(sf::Vector2f(size_.x, size_.y));
    bar_.setPosition(sf::Vector2f(0, 0));
    bar_.setScale(sf::Vector2f(percentage_, 1));

    RenderTexture();
}

HPBar::~HPBar()
{}

void HPBar::Draw(Camera& camera) const
{
    camera.Draw(sprite_, layer_main);
}

void HPBar::SetPercentage(const float percentage)
{
    percentage_ = percentage;
    RenderTexture();
}

void HPBar::SetPosition(const sf::Vector2f& position)
{
    position_ = position;
    sprite_.setPosition(position_);
}

void HPBar::RenderTexture()
{
    sf::RenderTexture render_texture;
    render_texture.create(size_.x, size_.y);
    render_texture.clear(sf::Color::Transparent);

    bar_.setScale(sf::Vector2f(percentage_, 1));
    if (percentage_ <= (1.0f/3.0f)) bar_.setFillColor(sf::Color::Red);
    else if (percentage_ <= (2.0f/3.0f)) bar_.setFillColor(sf::Color::Yellow);
    else bar_.setFillColor(sf::Color::Green);
    render_texture.draw(bar_);
    if (outlineFlag_) render_texture.draw(outline_);
    
    render_texture.display();
    texture_ = render_texture.getTexture();
    sprite_ = sf::Sprite(texture_);
    sprite_.setPosition(position_);
    sprite_.setOrigin(sf::Vector2f(size_.x / 2, size_.y / 2));
}
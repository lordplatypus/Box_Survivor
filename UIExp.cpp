#include "UIExp.h"
#include "ID.h"

UIExp::UIExp(int max_experience, int current_experience, const sf::Vector2f& position)
{
    name_ = "UIExp";
    tag_ = "UI";
    position_ = position;
    layerID_ = layer_UI;
    ID_ = 0;
    imageWidth_ = 32 * 10;
    imageHeight_ = 32;
    max_experience_ = max_experience;
    current_experience_ = current_experience;

    outline_.setSize(sf::Vector2f(imageWidth_-8, imageHeight_-8));
    outline_.setFillColor(sf::Color::Transparent);
    outline_.setOutlineColor(sf::Color::White);
    outline_.setOutlineThickness(4);
    outline_.setPosition(sf::Vector2f(4, 4));
    bar_.setFillColor(sf::Color::White);
    bar_.setPosition(sf::Vector2f(0, 0));

    RenderTexture();
}

UIExp::~UIExp()
{}

void UIExp::Draw(Camera& camera) const
{
    camera.Draw(sprite_, layerID_);
}

void UIExp::SetCurrentExperience(const int current_experience)
{
    current_experience_ = current_experience;
    RenderTexture();
}

void UIExp::SetMaxExperience(const int max_experience)
{
    max_experience_ = max_experience;
    RenderTexture();
}

void UIExp::RenderTexture()
{
    sf::RenderTexture render_texture;
    render_texture.create(imageWidth_, imageHeight_);
    render_texture.clear(sf::Color::Transparent);

    render_texture.draw(outline_);
    bar_.setSize(sf::Vector2f((float(current_experience_) / float(max_experience_)) * imageWidth_, imageHeight_));
    render_texture.draw(bar_);
    
    render_texture.display();
    texture_ = render_texture.getTexture();
    sprite_ = sf::Sprite(texture_);
    sprite_.setPosition(position_);
}
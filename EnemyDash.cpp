#include "EnemyDash.h"
#include "ID.h"
#include "Math.h"
#include <cmath>

EnemyDash::EnemyDash(const sf::Vector2f& position, const sf::Vector2f& destination, int thickness, float lifespan)
{
    name_ = "Dash";
    tag_ = "Enemy";
    ID_ = 0;
    layerID_ = layer_main;
    position_ = position;
    destination_ = destination;
    imageWidth_ = sqrt(pow(destination_.x - position_.x, 2) + pow(destination_.y - position_.y, 2));
    imageHeight_ = thickness;
    lifespan_ = lifespan;
    SetActive(false);

    sf::Vector2f normal = Normalize(sf::Vector2f(destination_.x - position_.x, destination_.y - position_.y));
    float angle = Math::RadToDeg(atan2(normal.y, normal.x));

    outline_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    outline_.setFillColor(sf::Color::Transparent);
    outline_.setOutlineColor(sf::Color(255, 255, 0, 255));
    outline_.setOutlineThickness(4.0f);
    outline_.setOrigin(sf::Vector2f(0, imageHeight_/2));
    outline_.setPosition(position_);
    outline_.setRotation(angle);

    fill_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    fill_.setFillColor(sf::Color(255, 255, 0, 255));
    fill_.setOrigin(sf::Vector2f(0, imageHeight_/2));
    fill_.setPosition(position_);
    fill_.setRotation(angle);
    fill_.setScale(sf::Vector2f(1, 0));
}

void EnemyDash::Update(float delta_time)
{
    life_ += delta_time;
    if (life_ >= lifespan_) Kill();
    else fill_.setScale(sf::Vector2f(1, life_ / lifespan_));
}

void EnemyDash::Draw(Camera& camera) const
{
    camera.Draw(outline_, layerID_);
    camera.Draw(fill_, layerID_);
}

void EnemyDash::Kill()
{
    isDead_ = true;
}
#include <cmath>
#include "Player.h"
#include "ID.h"
#include "Bullet.h"

Player::Player(Scene& scene, Camera& camera, Map& map, PlayerStats& ps, const sf::Vector2f& position)
{
    scene_ = &scene;
    camera_ = &camera;
    map_ = &map;
    ps_ = &ps;
    name_ = "Player";
    tag_ = "Player";
    position_ = position;
    layerID_ = layer_main;
    ID_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(255, 255, 255, 255));
    rect_.setPosition(position_);
}

Player::~Player()
{
    
}

void Player::Update(float delta_time)
{
    //Calculations go here
    InputHandle(delta_time);
}

void Player::InputHandle(float delta_time)
{
    if (shootTimer_ <= ps_->GetFireRate()) shootTimer_ += delta_time;
    if (invincibilityTimer_ >= 0.0f) invincibilityTimer_ -= delta_time;
    sf::Vector2f moveTo = position_;
    if (IP_.GetButton(sf::Keyboard::W))
    {
        moveTo.y -= ps_->GetPlayerSpeed() * delta_time;
    }
    if (IP_.GetButton(sf::Keyboard::A))
    {
        moveTo.x -= ps_->GetPlayerSpeed() * delta_time;
    }
    if (IP_.GetButton(sf::Keyboard::S))
    {
        moveTo.y += ps_->GetPlayerSpeed() * delta_time;
    }
    if (IP_.GetButton(sf::Keyboard::D))
    {
        moveTo.x += ps_->GetPlayerSpeed() * delta_time;
    }
    if (IP_.GetButton(sf::Mouse::Left) && shootTimer_ >= ps_->GetFireRate())
    {
        sf::Vector2f distance = IP_.GetMousePosition(*camera_) - camera_->GetView(view_main).getSize() / 2.0f; // mouse position is local pos not world coords
        float angle = atan(distance.x / distance.y); // get angle from center of the view to mouse pos

        sf::Vector2f xy = sf::Vector2f(sin(angle), cos(angle)); // x and y of triangle at the above angle
        if (distance.y < 0) xy *= -1.0f; // reverse xy if mouse is above the middle of view (distance.y < 0)
        sf::Vector2f bulletVelocity = xy * ps_->GetBulletSpeed(); // set bullet velocity
        sf::Vector2f startPos = sf::Vector2f(position_.x + (imageWidth_ / 2), position_.y + (imageHeight_ / 2)); // add xy to player pos

        scene_->AddGameObject(new Bullet(*map_, startPos, bulletVelocity, ps_->GetBulletRange()));
        shootTimer_ = 0.0f;
    }

    if (Transversable(moveTo))
    {
        position_ = moveTo;
        rect_.setPosition(position_);
    }

    camera_->SetViewCenter(view_main, sf::Vector2(position_.x + imageWidth_ / 2, position_.y + imageHeight_ / 2));

    IP_.Update();
}

void Player::Draw(Camera& camera) const
{
    if (!CanTakeDamage() && (int)(invincibilityTimer_ * 100.0f) % 2 == 1) return;
    camera.Draw(rect_, layer_main);
}

void Player::TakeDamage()
{
    invincibilityTimer_ = ps_->GetInvincibilityTime();
}

bool Player::CanTakeDamage() const
{
    if (invincibilityTimer_ > 0.0f) return false;
    return true;
}

void Player::ReactOnCollision(GameObject& other)
{}

bool Player::Transversable(const sf::Vector2f& position) const
{
    if (!map_->Transversable(position)) return false;
    if (!map_->Transversable(sf::Vector2f(position.x, position.y + imageHeight_))) return false;
    if (!map_->Transversable(sf::Vector2f(position.x + imageWidth_, position.y))) return false;
    if (!map_->Transversable(sf::Vector2f(position.x + imageWidth_, position.y + imageHeight_))) return false;
    return true;
}
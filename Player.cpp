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
    velocity_ = sf::Vector2f(300.0f, 300.0f);
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
    sf::Vector2f moveTo = position_;
    if (IP_.GetButton(sf::Keyboard::W))
    {
        float moveUp = position_.y - velocity_.y * delta_time;
        if (map_->Transversable(sf::Vector2f(position_.x, moveUp))) moveTo.y = moveUp;
    }
    if (IP_.GetButton(sf::Keyboard::A))
    {
        float moveLeft = position_.x - velocity_.x * delta_time;
        if (map_->Transversable(sf::Vector2f(moveLeft, position_.y))) moveTo.x = moveLeft;
    }
    if (IP_.GetButton(sf::Keyboard::S))
    {
        float moveDown = position_.y + velocity_.y * delta_time;
        if (map_->Transversable(sf::Vector2f(position_.x, moveDown + imageHeight_))) moveTo.y = moveDown;
    }
    if (IP_.GetButton(sf::Keyboard::D))
    {
        float moveRight = position_.x + velocity_.x * delta_time;
        if (map_->Transversable(sf::Vector2f(moveRight + imageWidth_, position_.y))) moveTo.x = moveRight;
    }
    if (IP_.GetButtonDown(sf::Mouse::Left))
    {
        sf::Vector2f distance = IP_.GetMousePosition(*camera_) - camera_->GetView(view_main).getSize() / 2.0f; // mouse position is local pos not world coords
        float angle = atan(distance.x / distance.y); // get angle from center of the view to mouse pos

        sf::Vector2f xy = sf::Vector2f(sin(angle), cos(angle)); // x and y of triangle at the above angle
        if (distance.y < 0) xy *= -1.0f; // reverse xy if mouse is above the middle of view (distance.y < 0)
        sf::Vector2f bulletVelocity = xy * 500.0f; // set bullet velocity
        xy *= 32.0f; // move out 32 pixels, so the bullets don't interfer with the player hitbox
        sf::Vector2f startPos = sf::Vector2f((position_.x + imageWidth_ / 2) + xy.x, (position_.y + imageHeight_ / 2) + xy.y); // add xy to player pos

        scene_->AddGameObject(new Bullet(*map_, "Player_Bullet", startPos, bulletVelocity, 1.0f));
    }

    position_ = moveTo;
    rect_.setPosition(position_);
    camera_->SetViewCenter(view_main, sf::Vector2(position_.x + imageWidth_ / 2, position_.y + imageHeight_ / 2));

    IP_.Update();
}

void Player::Draw(Camera& camera) const
{
    //Draw sprite to layer
    //camera.Draw(sprite_, layer_main);
    camera.Draw(rect_, layer_main);
}

void Player::DelayedDraw(Camera& camera) const
{
    //same as Draw
    //this function will be called after Draw
    //Good for things that need to be drawn last - UI
}

void Player::ReactOnCollision(GameObject& other)
{
    //If Object B collided with this Object (A), then B's info is sent to A

    if (other.GetName() == "Player")
    {
        //EX: if the collided object is "player" then do this
    }
}
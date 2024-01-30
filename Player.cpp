#include "Player.h"
#include "ID.h"

Player::Player(Scene& scene, Camera& camera, Map& map, const sf::Vector2f& position)
{
    scene_ = &scene;
    camera_ = &camera;
    map_ = &map;
    name_ = "Player";
    tag_ = "Player";
    position_ = position;
    velocity_ = sf::Vector2f(500.0f, 500.0f);
    layerID_ = layer_main;
    ID_ = 0;
    imageWidth_ = 32;
    imageHeight_ = 32;

    // sf::RectangleShape test(sf::Vector2f(imageWidth_, imageHeight_));
    // // rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    // rect_ = test;
    // rect_ = sf::RectangleShape(sf::Vector2f(16, 16));
    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(255, 255, 255, 255));
    rect_.setPosition(position_);

    //Sprite set up
    //sprite_ = LP.SetSprite(pic_texture, position_);
}

Player::~Player()
{}

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
#include "GameOver.h"
#include "ID.h"

GameOver::GameOver(Scene& scene, LP& LP, const sf::Vector2f& position)
{
    scene_ = &scene;
    name_ = "GameOver";
    tag_ = "UI";
    position_ = position;
    layerID_ = layer_UI;
    ID_ = 0;
    imageWidth_ = 0;
    imageHeight_ = 0;

    text_ = LP.SetText(main_font, "Game Over: Press Space to Return to the Title");
    LP.SetTextOriginCenter(text_);
    text_.setPosition(position_);
}

GameOver::~GameOver()
{}

void GameOver::Update(float delta_time)
{
    if (IP_.GetButtonDown(sf::Keyboard::Space)) scene_->ChangeScene("Title");
    IP_.Update();
}

void GameOver::Draw(Camera& camera) const
{
    camera.Draw(text_, layerID_);
}
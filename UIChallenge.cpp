#include <cmath>
#include "UIChallenge.h"
#include "ID.h"

UIChallenge::UIChallenge(LP& LP, const sf::Vector2f& position)
{
    name_ = "UIChallenge";
    tag_ = "UI";
    position_ = position;
    layerID_ = layer_UI;
    ID_ = 0;
    imageWidth_ = sqrt(pow(32, 2) + pow(32, 2));
    imageHeight_ = imageWidth_;

    text_ = LP.SetText(main_font, "");
}

UIChallenge::~UIChallenge()
{}

void UIChallenge::Draw(Camera& camera) const
{
    //Draw sprite to layer
    camera.Draw(text_, layerID_);
}

void UIChallenge::SetText(const std::string& new_text)
{
    text_.setString(new_text);
}

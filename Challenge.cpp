#include "Challenge.h"

Challenge::Challenge()
{}

Challenge::~Challenge()
{}

void Challenge::Init(const std::string& name, const std::string& challenge_text, 
                     PlayerManager* player_manager, Staircase* staircase)
{
    name_ = name;
    tag_ = "Challenge";
    SetChallengeText(challenge_text);
    player_manager_ = player_manager;
    player_manager_->SetChallengeText(GetChallengeText());
    staircase_ = staircase;
    staircase_->SetLock(true);
    SetActive(false); // deactivate this object for collision calcs
}

void Challenge::Update(float delta_time)
{
    ChallengeUpdate();
}

void Challenge::SetChallengeText(const std::string& challenge_text)
{
    challenge_text_ = challenge_text;
}

const std::string& Challenge::GetChallengeText() const
{
    return challenge_text_;
}


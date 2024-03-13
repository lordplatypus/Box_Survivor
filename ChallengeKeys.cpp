#include "ChallengeKeys.h"

ChallengeKeys::ChallengeKeys(PlayerManager& playerManager, Staircase& staircase, const int neededKeys)
{
    currentKeys_ = 0;
    neededKeys_ = neededKeys;
    Init("ChallengeKeys", "Keys Needed: " + std::to_string(currentKeys_) + " / " + std::to_string(neededKeys_), &playerManager, &staircase);
}

ChallengeKeys::~ChallengeKeys()
{}

void ChallengeKeys::Update(float delta_time)
{}

void ChallengeKeys::KeyCollected()
{
    currentKeys_++;
    ChallengeUpdate();
}

void ChallengeKeys::ChallengeUpdate()
{
    if (player_manager_ == nullptr || staircase_ == nullptr) return;
    
    player_manager_->SetChallengeText("Keys Needed: " + std::to_string(currentKeys_) + " / " + std::to_string(neededKeys_));
    if (currentKeys_ >= neededKeys_)
    {
        player_manager_->SetChallengeText("Challenge Complete - Stairs Unlocked");
        staircase_->SetLock(false);
        Kill();
    }
}
#include "ChallengeGhost.h"

ChallengeGhost::ChallengeGhost(PlayerManager& playerManager, Staircase& staircase, EnemyGhost& ghost, const float timeNeeded)
{
    time_ = 0.0f;
    timeNeeded_ = timeNeeded;
    ghost_ = &ghost;
    Init("ChallengeGhost", "Survive: " + std::to_string(time_) + " / " + std::to_string(timeNeeded_), &playerManager, &staircase);
}

ChallengeGhost::~ChallengeGhost()
{}

void ChallengeGhost::Update(float delta_time)
{
    time_ += delta_time;
    ChallengeUpdate();
}

void ChallengeGhost::ChallengeUpdate()
{
    if (player_manager_ == nullptr || staircase_ == nullptr) return;
    
    player_manager_->SetChallengeText("Survive: " + std::to_string(time_) + " / " + std::to_string(timeNeeded_));
    if (time_ >= timeNeeded_)
    {
        player_manager_->SetChallengeText("Challenge Complete - Stairs Unlocked");
        staircase_->SetLock(false);
        ghost_->Kill();
        Kill();
    }
}
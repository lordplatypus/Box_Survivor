#include "ChallengeKills.h"

ChallengeKills::ChallengeKills(SceneDungeon& scene, PlayerManager& playerManager, Staircase& staircase, int enemyNum, int neededKills)
{
    dungeonScene_ = &scene;
    currentKills_ = 0;
    previousKills_ = 0;
    neededKills_ = neededKills;
    enemyNum_ = enemyNum;
    Init("ChallengeKills", "Enemies Destroyed: " + std::to_string(currentKills_) + " / " + std::to_string(neededKills), &playerManager, &staircase);
}

ChallengeKills::~ChallengeKills()
{}

void ChallengeKills::ChallengeUpdate()
{
    currentKills_ = enemyNum_ - dungeonScene_->GetEnemyCount();
    if (currentKills_ != previousKills_ && player_manager_ != nullptr)
    {
        previousKills_ = currentKills_;
        player_manager_->SetChallengeText("Enemies Destroyed: " + std::to_string(currentKills_) + " / " + std::to_string(neededKills_));
        if (currentKills_ >= neededKills_ && staircase_ != nullptr)
        {
            player_manager_->SetChallengeText("Challenge Complete - Stairs Unlocked");
            staircase_->SetLock(false);
            Kill();
        }
    }
}
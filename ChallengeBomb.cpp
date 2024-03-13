#include "ChallengeBomb.h"
#include "EnemyBomb.h"

ChallengeBomb::ChallengeBomb(Scene& scene, PlayerManager& playerManager, Staircase& staircase, const float timeNeeded)
{
    scene_ = &scene;
    time_ = 0.0f;
    timeNeeded_ = timeNeeded;
    Init("ChallengeBomb", "Survive: " + std::to_string(time_) + " / " + std::to_string(timeNeeded_), &playerManager, &staircase);
}

ChallengeBomb::~ChallengeBomb()
{}

void ChallengeBomb::Update(float delta_time)
{
    time_ += delta_time;
    bombTimer_ += delta_time;
    ChallengeUpdate();
}

void ChallengeBomb::ChallengeUpdate()
{
    if (player_manager_ == nullptr || staircase_ == nullptr) return;
    
    player_manager_->SetChallengeText("Survive: " + std::to_string(time_) + " / " + std::to_string(timeNeeded_));
    if (time_ >= timeNeeded_)
    {
        player_manager_->SetChallengeText("Challenge Complete - Stairs Unlocked");
        staircase_->SetLock(false);
        Kill();
    }

    if (bombTimer_ < bombTime_) return;
    bombTimer_ = 0.0f;
    sf::Vector2f playerPosition = player_manager_->GetPlayer()->GetPosition();
    sf::Vector2f bombPos(playerPosition.x + 32 * (10 - (int)(std::rand() / ((RAND_MAX + 1u) / 21))), playerPosition.y + 32 * (10 - (int)(std::rand() / ((RAND_MAX + 1u) / 21))));
    int bombSize = 32 + std::rand() / ((RAND_MAX + 1u) / (32 * 4));
    float bombLifeSpan = 50 + std::rand() / ((RAND_MAX + 1u) / 100);
    bombLifeSpan /= 100.0f;
    scene_->AddGameObject(new EnemyBomb(*player_manager_, sf::Vector2f(bombPos.x, bombPos.y), sf::Vector2i(bombSize, bombSize), bombLifeSpan));
}
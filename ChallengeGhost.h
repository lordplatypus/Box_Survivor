#ifndef CHALLENGE_GHOST_H_
#define CHALLENGE_GHOST_H_
#include "Challenge.h"
#include "EnemyGhost.h"

class ChallengeGhost : public Challenge
{
public:
    ChallengeGhost(PlayerManager& playerManager, Staircase& staircase, EnemyGhost& ghost, const float timeNeeded);
    ~ChallengeGhost() override;
    virtual void Update(float delta_time) override;

private:
    virtual void ChallengeUpdate() override;

private:
    float time_{0.0f};
    float timeNeeded_{0.0f};
    EnemyGhost* ghost_{nullptr};
};

#endif
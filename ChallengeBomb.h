#ifndef CHALLENGE_BOMB_H_
#define CHALLENGE_BOMB_H_
#include "Challenge.h"

class ChallengeBomb : public Challenge
{
public:
    ChallengeBomb(Scene& scene, PlayerManager& playerManager, Staircase& staircase, const float timeNeeded);
    ~ChallengeBomb() override;
    virtual void Update(float delta_time) override;

private:
    virtual void ChallengeUpdate() override;

private:
    float time_{0.0f};
    float timeNeeded_{0.0f};
    float bombTime_{0.5f};
    float bombTimer_{0.0f};
};

#endif
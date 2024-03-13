#ifndef CHALLENGE_KEYS_H_
#define CHALLENGE_KEYS_H_
#include "Challenge.h"

class ChallengeKeys : public Challenge
{
public:
    ChallengeKeys(PlayerManager& playerManager, Staircase& staircase, const int neededKeys);
    ~ChallengeKeys() override;
    virtual void Update(float delta_time) override;

    void KeyCollected();

private:
    virtual void ChallengeUpdate() override;

private:
    int currentKeys_{0};
    int neededKeys_{0};
};

#endif
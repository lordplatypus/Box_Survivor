#ifndef CHALLENGEKILLS_H_
#define CHALLENGEKILLS_H_
#include "Challenge.h"
#include "SceneDungeon.h"

class ChallengeKills : public Challenge
{
public:
    ChallengeKills(SceneDungeon& scene, PlayerManager& playerManager, Staircase& staircase, int enemyNum, int neededKills);
    ~ChallengeKills() override;

private:
    virtual void ChallengeUpdate() override;

private:
    SceneDungeon* dungeonScene_{nullptr};
    int currentKills_{0};
    int neededKills_{0};
    int previousKills_{0};
    int enemyNum_{0};
};

#endif
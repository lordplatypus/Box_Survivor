#ifndef PLAYERMANAGER_H_
#define PLAYERMANAGER_H_
#include "Player.h"
#include "PlayerStats.h"
#include "UIHP.h"
#include "UIExp.h"
#include "UIChallenge.h"

class PlayerManager
{
public:
    PlayerManager(PlayerStats& ps, Player& player, Scene& scene, Camera& camera, LP& lp);
    ~PlayerManager();

    PlayerStats* GetPlayerStats() const;
    Player* GetPlayer() const;

    void UpdateUI();

    void DealDamage(int damage);
    void AddExperience(int experience);
    void SetChallengeText(const std::string challenge_text);

private:
    PlayerStats* ps_{nullptr};
    Player* player_{nullptr};
    Scene* scene_{nullptr};
    Camera* camera_{nullptr};
    LP* LP_{nullptr};
    UIHP* player_hp_ui_{nullptr};
    UIExp* player_exp_ui_{nullptr};
    UIChallenge* challenge_ui_{nullptr};
};

#endif
#ifndef PLAYERMANAGER_H_
#define PLAYERMANAGER_H_
// #include "Scene.h"
// #include "Map.h"
#include "Player.h"
#include "PlayerStats.h"
#include "UIHP.h"
#include "UIExp.h"

class PlayerManager
{
public:
    PlayerManager(PlayerStats& ps, Player& player, UIHP& player_hp_ui, UIExp& player_exp_ui);
    ~PlayerManager();

    PlayerStats* GetPlayerStats();

    void DealDamage(int damage);
    void AddExperience(int experience);

private:
    PlayerStats* ps_{nullptr};
    Player* player_{nullptr};
    UIHP* player_hp_ui_{nullptr};
    UIExp* player_exp_ui_{nullptr};
};

#endif
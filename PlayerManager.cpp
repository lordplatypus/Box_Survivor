#include "PlayerManager.h"

PlayerManager::PlayerManager(PlayerStats& ps, Player& player, UIHP& player_hp_ui, UIExp& player_exp_ui)
{
    ps_ = &ps;
    player_ = &player;
    player_hp_ui_ = &player_hp_ui;
    player_exp_ui_ = &player_exp_ui;
}

PlayerManager::~PlayerManager() {}

PlayerStats* PlayerManager::GetPlayerStats() {return ps_;}

void PlayerManager::DealDamage(int damage)
{
    int new_hp = ps_->GetHP() - damage; // get current hp
    if (new_hp <= 0) player_->Kill(); // if hp is <= 0 then kill player
    ps_->SetHP(new_hp); // set new hp
    // update player hp ui here
    player_hp_ui_->SetCurrentHP(ps_->GetHP());
}

void PlayerManager::AddExperience(int experience)
{
    int total_experience = ps_->GetExperience() + experience; // get exp + new exp
    if (total_experience >= ps_->GetMaxExperience())
    { // if exp is enough for a level up
        ps_->SetLevel(ps_->GetLevel() + 1); // Level + 1
        total_experience -= ps_->GetMaxExperience(); // Roll over exp
        ps_->SetMaxExperience(ps_->GetMaxExperience() * 2); // increase needed exp for level up
    }
    ps_->SetExperience(total_experience); // set new exp
    // update experience and level UI here
    player_exp_ui_->SetMaxExperience(ps_->GetMaxExperience());
    player_exp_ui_->SetCurrentExperience(ps_->GetExperience());
}
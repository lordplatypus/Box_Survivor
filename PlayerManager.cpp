#include "PlayerManager.h"
#include "ID.h"
#include "GameOver.h"

PlayerManager::PlayerManager(PlayerStats& ps, Player& player, Scene& scene, Camera& camera, LP& lp)
{
    ps_ = &ps;
    player_ = &player;
    scene_ = &scene;
    camera_ = &camera;
    LP_ = &lp;
    // player_hp_ui_ = &player_hp_ui;
    // player_exp_ui_ = &player_exp_ui;

    player_hp_ui_ = new UIHP(ps_->GetMaxHP(), ps_->GetHP(), sf::Vector2f(32, camera.GetView(view_UI).getSize().y - 64));
    player_exp_ui_ = new UIExp(ps_->GetMaxExperience(), ps_->GetExperience(), sf::Vector2f(camera.GetView(view_UI).getSize().x - 320 - 32, camera.GetView(view_UI).getSize().y - 64));
    challenge_ui_ = new UIChallenge(lp, sf::Vector2f(64, 64));

    scene_->AddGameObject(player_hp_ui_);
    scene_->AddGameObject(player_exp_ui_);
    scene_->AddGameObject(challenge_ui_);
}

PlayerManager::~PlayerManager() {}

PlayerStats* PlayerManager::GetPlayerStats() const {return ps_;}

Player* PlayerManager::GetPlayer() const {return player_;}

void PlayerManager::UpdateUI()
{
    player_hp_ui_->SetMaxHP(ps_->GetMaxHP());
    player_hp_ui_->SetCurrentHP(ps_->GetHP());
}

void PlayerManager::DealDamage(int damage)
{
    if (!player_->CanTakeDamage()) return; // if player is invincibile, return
    int new_hp = ps_->GetHP() - damage; // get current hp
    player_->TakeDamage();
    if (new_hp <= 0) 
    {// if hp is <= 0 then kill player
        player_->Kill();
        scene_->AddGameObject(new GameOver(*scene_, *LP_, camera_->GetView(view_UI).getCenter(), "Game Over: Press Space to Return to the Title"));
    }
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
        ps_->SetMaxExperience(ps_->GetMaxExperience() * 1.5f); // increase needed exp for level up
        scene_->ChangeScene("Upgrade"); // change to the upgrade scene
    }
    ps_->SetExperience(total_experience); // set new exp
    // update experience and level UI here
    player_exp_ui_->SetMaxExperience(ps_->GetMaxExperience());
    player_exp_ui_->SetCurrentExperience(ps_->GetExperience());
}

void PlayerManager::SetChallengeText(const std::string challenge_text)
{
    challenge_ui_->SetText(challenge_text);
}
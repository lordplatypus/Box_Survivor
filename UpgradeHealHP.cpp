#include "UpgradeHealHP.h"

UpgradeHealHP::UpgradeHealHP(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    // healAmount_ = 1 + std::rand() / ((RAND_MAX + 1u) / 3);
    healAmount_ = 1;
    Init(lp, playerStats, worldPosition, "Heals the\nPlayer by " + std::to_string(healAmount_));
}

UpgradeHealHP::~UpgradeHealHP()
{}

void UpgradeHealHP::Apply()
{
    int hp = playerStats_->GetHP() + healAmount_;
    if (hp > playerStats_->GetMaxHP()) hp = playerStats_->GetMaxHP();
    playerStats_->SetHP(hp);
}
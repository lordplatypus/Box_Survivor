#include "UpgradeDamage.h"

UpgradeDamage::UpgradeDamage(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    Init(lp, playerStats, worldPosition, "Increases the\nPlayers Damage\nby 1");
}

UpgradeDamage::~UpgradeDamage()
{}

void UpgradeDamage::Apply()
{
    playerStats_->SetDamage(playerStats_->GetDamage() + 1);
}
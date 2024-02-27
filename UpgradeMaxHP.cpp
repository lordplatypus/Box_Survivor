#include "UpgradeMaxHP.h"

UpgradeMaxHP::UpgradeMaxHP(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    Init(lp, playerStats, worldPosition, "Increases the\nPlayers Max\nHP by 1");
}

UpgradeMaxHP::~UpgradeMaxHP()
{}

void UpgradeMaxHP::Apply()
{
    playerStats_->SetMaxHP(playerStats_->GetMaxHP() + 1);
}
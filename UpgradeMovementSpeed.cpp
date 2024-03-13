#include "UpgradeMovementSpeed.h"

UpgradeMovementSpeed::UpgradeMovementSpeed(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    Init(lp, playerStats, worldPosition, "Increases the\nPlayers Speed\nby 50");
}

UpgradeMovementSpeed::~UpgradeMovementSpeed()
{}

void UpgradeMovementSpeed::Apply()
{
    playerStats_->SetPlayerSpeed(playerStats_->GetPlayerSpeed() + 50);
}
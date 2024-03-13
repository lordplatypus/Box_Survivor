#include "UpgradeInvincibilityTime.h"

UpgradeInvincibilityTime::UpgradeInvincibilityTime(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    Init(lp, playerStats, worldPosition, "Increases the\nPlayers\nInvincibility\nframes by\n0.1 seconds");
}

UpgradeInvincibilityTime::~UpgradeInvincibilityTime()
{}

void UpgradeInvincibilityTime::Apply()
{
    playerStats_->SetInvincibilityTime(playerStats_->GetInvincibilityTime() + 0.1f);
}
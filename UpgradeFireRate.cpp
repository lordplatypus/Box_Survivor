#include "UpgradeFireRate.h"

UpgradeFireRate::UpgradeFireRate(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    Init(lp, playerStats, worldPosition, "Increases the\nPlayers Fire\nRate by 25%");
}

UpgradeFireRate::~UpgradeFireRate()
{}

void UpgradeFireRate::Apply()
{
    float currentFireRate = playerStats_->GetFireRate();
    float newFireRate = currentFireRate * (3.0f / 4.0f);
    playerStats_->SetFireRate(newFireRate);
}
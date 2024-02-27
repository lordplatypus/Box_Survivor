#include "UpgradeBulletSpeed.h"

UpgradeBulletSpeed::UpgradeBulletSpeed(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    Init(lp, playerStats, worldPosition, "Increases\nBullet Speed\nby 100");
}

UpgradeBulletSpeed::~UpgradeBulletSpeed()
{}

void UpgradeBulletSpeed::Apply()
{
    playerStats_->SetBulletSpeed(playerStats_->GetBulletSpeed() + 100.0f);
}
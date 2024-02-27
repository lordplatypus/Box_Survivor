#include "UpgradeBulletRange.h"

UpgradeBulletRange::UpgradeBulletRange(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition)
{
    Init(lp, playerStats, worldPosition, "Increases\nBullet Range\nby 0.1");
}

UpgradeBulletRange::~UpgradeBulletRange()
{}

void UpgradeBulletRange::Apply()
{
    playerStats_->SetBulletRange(playerStats_->GetBulletRange() + 0.1f);
}
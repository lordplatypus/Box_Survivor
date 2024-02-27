#ifndef UPGRADE_BULLET_SPEED_H_
#define UPGRADE_BULLET_SPEED_H_
#include "Upgrade.h"

class UpgradeBulletSpeed : public Upgrade
{
public:
    UpgradeBulletSpeed(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeBulletSpeed() override;
    virtual void Apply() override;
};

#endif
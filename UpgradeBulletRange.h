#ifndef UPGRADE_BULLET_RANGE_H_
#define UPGRADE_BULLET_RANGE_H_
#include "Upgrade.h"

class UpgradeBulletRange : public Upgrade
{
public:
    UpgradeBulletRange(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeBulletRange() override;
    virtual void Apply() override;
};

#endif
#ifndef UPGRADE_FIRE_RATE_H_
#define UPGRADE_FIRE_RATE_H_
#include "Upgrade.h"

class UpgradeFireRate : public Upgrade
{
public:
    UpgradeFireRate(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeFireRate() override;
    virtual void Apply() override;
};

#endif
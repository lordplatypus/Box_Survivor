#ifndef UPGRADE_MOVEMENT_SPEED_H_
#define UPGRADE_MOVEMENT_SPEED_H_
#include "Upgrade.h"

class UpgradeMovementSpeed : public Upgrade
{
public:
    UpgradeMovementSpeed(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeMovementSpeed() override;
    virtual void Apply() override;
};

#endif
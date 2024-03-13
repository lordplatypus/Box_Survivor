#ifndef UPGRADE_INVINCIBILITY_TIME_H_
#define UPGRADE_INVINCIBILITY_TIME_H_
#include "Upgrade.h"

class UpgradeInvincibilityTime : public Upgrade
{
public:
    UpgradeInvincibilityTime(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeInvincibilityTime() override;
    virtual void Apply() override;
};

#endif
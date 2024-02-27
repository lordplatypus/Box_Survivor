#ifndef UPGRADE_DAMAGE_H_
#define UPGRADE_DAMAGE_H_
#include "Upgrade.h"

class UpgradeDamage : public Upgrade
{
public:
    UpgradeDamage(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeDamage() override;
    virtual void Apply() override;
};

#endif
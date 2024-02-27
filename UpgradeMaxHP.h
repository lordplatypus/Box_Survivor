#ifndef UPGRADE_MAX_HP_H_
#define UPGRADE_MAX_HP_H_
#include "Upgrade.h"

class UpgradeMaxHP : public Upgrade
{
public:
    UpgradeMaxHP(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeMaxHP() override;
    virtual void Apply() override;
};

#endif
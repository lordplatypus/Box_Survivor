#ifndef UPGRADE_HEAL_HP_H_
#define UPGRADE_HEAL_HP_H_
#include "Upgrade.h"

class UpgradeHealHP : public Upgrade
{
public:
    UpgradeHealHP(LP& lp, PlayerStats& playerStats, const sf::Vector2f& worldPosition);
    ~UpgradeHealHP() override;
    virtual void Apply() override;

private:
    int healAmount_{0};
};

#endif
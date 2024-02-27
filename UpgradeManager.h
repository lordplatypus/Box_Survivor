#ifndef UPGRADE_MANAGER_H_
#define UPGRADE_MANAGER_H_
#include "GameObject.h"
#include "PlayerStats.h"
#include "Upgrade.h"
#include "IP.h"
#include "LP.h"

class UpgradeManager : public GameObject
{
public:
    UpgradeManager(Scene& scene, const std::string& previousScene, LP& lp, PlayerStats& playerStats);
    ~UpgradeManager();
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;

private:
    void PickUpgrades();
    void RenderUpgrades();

private:
    std::string previousScene_{""};
    LP* lp_{nullptr};
    IP IP_;
    PlayerStats* playerStats_{nullptr};
    std::vector<Upgrade*> upgrades_;
    int selected_{1};
};

#endif
#include "UpgradeManager.h"
// Upgrades
#include "UpgradeMaxHP.h"
#include "UpgradeHealHP.h"
#include "UpgradeMovementSpeed.h"
#include "UpgradeBulletRange.h"
#include "UpgradeBulletSpeed.h"
#include "UpgradeDamage.h"

UpgradeManager::UpgradeManager(Scene& scene, const std::string& previousScene, LP& lp, PlayerStats& playerStats)
{
    scene_ = &scene;
    previousScene_ = previousScene;
    lp_ = &lp;
    playerStats_ = &playerStats;
    name_ = "UpgradeManager";
    tag_ = "UpgradeManager";
    ID_ = 0;

    SetActive(false);

    PickUpgrades();
}

UpgradeManager::~UpgradeManager()
{
    for (auto upgrade : upgrades_)
    {
        delete upgrade;
    }
    upgrades_.clear();
}

void UpgradeManager::Update(float delta_time)
{
    if (IP_.GetButtonDown(sf::Keyboard::Space))
    {
        upgrades_[selected_]->Apply();
        scene_->ChangeScene(previousScene_);
    }
    if (IP_.GetButtonDown(sf::Keyboard::A))
    {
        selected_--;
        if (selected_ < 0) selected_ = 2;
        RenderUpgrades();
    }
    if (IP_.GetButtonDown(sf::Keyboard::D))
    {
        selected_++;
        if (selected_ > 2) selected_ = 0;
        RenderUpgrades();
    }

    IP_.Update();
}

void UpgradeManager::Draw(Camera& camera) const
{
    for (auto upgrade : upgrades_)
    {
        upgrade->Draw(camera);
    }
}

void UpgradeManager::PickUpgrades()
{
    int upgradeNum = 6;
    std::vector<int> upgradeIDs;
    std::vector<int> IDs;
    for (int i = 0; i < upgradeNum; i++) IDs.push_back(i);
    for (int i = 0; i < 3; i++)
    {
        int randomID = std::rand() / ((RAND_MAX + 1u) / IDs.size());
        upgradeIDs.push_back(IDs[randomID]);
        IDs.erase(IDs.begin() + randomID);
    }

    for (int i = 0; i < upgradeIDs.size(); i++)
    {
        sf::Vector2f upgradePos(16 + 32*i + 14*32*i, 32);
        switch (upgradeIDs[i])
        {
            default:
                upgrades_.push_back(new UpgradeMaxHP(*lp_, *playerStats_, upgradePos));
                break;

            case 1:
                upgrades_.push_back(new UpgradeHealHP(*lp_, *playerStats_, upgradePos));
                break;

            case 2:
                upgrades_.push_back(new UpgradeMovementSpeed(*lp_, *playerStats_, upgradePos));
                break;

            case 3:
                upgrades_.push_back(new UpgradeBulletRange(*lp_, *playerStats_, upgradePos));
                break;

            case 4:
                upgrades_.push_back(new UpgradeBulletSpeed(*lp_, *playerStats_, upgradePos));
                break;

            case 5:
                upgrades_.push_back(new UpgradeDamage(*lp_, *playerStats_, upgradePos));
                break;
        }
    }

    upgrades_[1]->Select();
}

void UpgradeManager::RenderUpgrades()
{
    for (int i = 0; i < upgrades_.size(); i++)
    {
        if (i == selected_) upgrades_[i]->Select();
        else upgrades_[i]->UnSelect();
    }
}
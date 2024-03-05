#ifndef ENEMY_H_
#define ENEMY_H_
#include "GameObject.h"
#include "PlayerManager.h"
#include "SceneDungeon.h"
#include "Map.h"
#include "HPBar.h"

class Enemy : public GameObject
{
public:
    ~Enemy() override;
    virtual void Init(SceneDungeon* dungeonScene, Map* map, PlayerManager* playerManager, const std::string& name, int id, const sf::Vector2i& size, const sf::Vector2f& position, int perceptionRange, int maxHP, int attackPower, float speed, int exp);
    virtual bool SeePlayer() const;
    bool Transversable(const sf::Vector2f& position) const;
    sf::IntRect GetPerceptionArea() const;
    sf::Vector2f Normalize(const sf::Vector2f& vector);
    virtual void TakeDamage();
    virtual void Kill() override;

protected:
    SceneDungeon* dungeonScene_{nullptr};
    Map* map_{nullptr};
    PlayerManager* playerManager_{nullptr};
    HPBar* hpBar_{nullptr};
    int perceptionRange_{0};
    bool seePlayerFlag_{false};

    int HP_{0};
    int maxHP_{0};
    int attackPower_{0};
    int exp_{0};
};

#endif
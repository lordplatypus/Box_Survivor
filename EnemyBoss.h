#ifndef ENEMY_BOSS_H_
#define ENEMY_BOSS_H_
#include "Enemy.h"

class EnemyBoss : public Enemy
{
public:
    EnemyBoss(Scene& scene, Map& map, PlayerManager& playerManager, Camera& camera, LP& lp, const sf::Vector2f& position);
    void Update(float delta_time) override;
    void Draw(Camera& camera) const override;
    virtual void TakeDamage() override;
    virtual void Kill() override;

private:
    void ReactOnCollision(GameObject& other) override;

    float AngleToPlayer();

    void Shoot(float delta_time);
    void Bomb(float delta_time);
    void Dash(float delta_time);
    void Laser(float delta_time);
    void Nuke(float delta_time);

private:
    enum attacks_{none, shoot, bomb, dash, laser, nuke};
    attacks_ currentAttack_{none};
    Camera* camera_{nullptr};
    LP* lp_{nullptr};
    sf::RectangleShape rect_;
    bool enrage_{false};

    // Attacks
    float nextAttack_{8.0f};
    float attackTimer_{0.0f};
    // shooting
    float currentRads_{1.0f};
    float shootTimer_{0.0f};
    // bomb
    float nextBomb_{0.0f};
    float bombTimer_{0.0f};
    float bombDone_{2.0f};
    // dash
    int currentKey_{0};
    std::vector<sf::Vector2f> potentialDestinations_ = 
    {
        sf::Vector2f(64 * 32 / 2, 64 * 32 / 2),
        sf::Vector2f(16 * 32, 16 * 32),
        sf::Vector2f(16 * 3 * 32, 16 * 32),
        sf::Vector2f(16 * 32, 16 * 3 * 32),
        sf::Vector2f(16 * 3 * 32, 16 * 3 * 32)
    };
    int dashNum_{0};
    float dashTime_{1.0f};
    float dashTimer_{0.0f};
};

#endif
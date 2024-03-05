#include "EnemyBoss.h"
#include "Math.h"
#include "ID.h"
#include "GameOver.h"
#include "EnemyBullet.h"
#include "EnemyBomb.h"
#include "EnemyLaser.h"
#include "EnemyDash.h"

EnemyBoss::EnemyBoss(Scene& scene, Map& map, PlayerManager& playerManager, Camera& camera, LP& lp, const sf::Vector2f& position)
{
    scene_ = &scene;
    map_ = &map;
    playerManager_ = &playerManager;
    camera_ = &camera;
    lp_ = &lp;
    name_ = "Boss";
    tag_ = "Enemy";
    ID_ = 0;
    layerID_ = layer_main;
    imageWidth_ = 32 * 5;
    imageHeight_ = 32 * 5;
    SetLeft(-imageWidth_/2);
    SetTop(-imageWidth_/2);
    SetRight(imageWidth_/2);
    SetBottom(imageWidth_/2);
    position_ = position;
    perceptionRange_ = 320;
    maxHP_ = 500;
    HP_ = 251;
    attackPower_ = 1;
    velocity_ = sf::Vector2f(1000, 1000);

    hpBar_ = new HPBar(sf::Vector2f(position_.x, position_.y - imageHeight_), sf::Vector2i(imageWidth_, imageHeight_ / 4), (float)HP_ / (float)maxHP_, true);

    rect_.setSize(sf::Vector2f(imageWidth_, imageHeight_));
    rect_.setFillColor(sf::Color(126, 126, 126, 255));
    rect_.setOrigin(sf::Vector2f(imageWidth_/2, imageHeight_/2));
    rect_.setPosition(position_);
    
    // currentAttack_ = dash;
    // enrage_ = true;
}

void EnemyBoss::Update(float delta_time)
{
    if (currentAttack_ == bomb)
    {
        Bomb(delta_time);
    }
    else if (currentAttack_ == dash)
    {
        Dash(delta_time);
    }
    else if (currentAttack_ == laser)
    {
        Laser(delta_time);
    }
    else if (currentAttack_ == nuke)
    {
        Nuke(delta_time);
    }
    else
    {
        attackTimer_ += delta_time;
        if (attackTimer_ >= nextAttack_)
        {
            currentAttack_ = static_cast<attacks_>(1 + std::rand() / ((RAND_MAX + 1u) / 5));
            // currentAttack_ = bomb;
            attackTimer_ = 0.0f;
        }
        if (currentAttack_ == shoot) Shoot(delta_time);
    }
}

void EnemyBoss::Draw(Camera& camera) const
{
    camera.Draw(rect_, layerID_);
    hpBar_->Draw(camera);
}

void EnemyBoss::ReactOnCollision(GameObject& other)
{
    if (other.GetName() == "Player")
    {
        playerManager_->DealDamage(1);
    }
    else if (other.GetName() == "Player_Bullet")
    {
        TakeDamage();
    }
}

void EnemyBoss::TakeDamage()
{
    HP_ -= playerManager_->GetPlayerStats()->GetDamage();
    hpBar_->SetPercentage((float)HP_ / (float)maxHP_);
    if (HP_ <= 0)
    {
        playerManager_->AddExperience(exp_);
        Kill();
    }
    else if (HP_ < maxHP_ / 2) enrage_ = true;
}

void EnemyBoss::Kill()
{
    isDead_ = true;
    scene_->AddGameObject(new GameOver(*scene_, *lp_, camera_->GetView(view_UI).getCenter(), "Congratulations You Win!\nPress Space to Return to the Title"));
}

float EnemyBoss::AngleToPlayer()
{
    sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
    sf::Vector2f normal = Normalize(sf::Vector2f(playerPosition.x - position_.x, playerPosition.y - position_.y));
    return Math::RadToDeg(atan2(normal.y, normal.x));
}

void EnemyBoss::Shoot(float delta_time)
{
    shootTimer_ += delta_time;
    if (shootTimer_ < 0.2f) return;

    shootTimer_ = 0.0f;
    sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
    sf::Vector2f normal = Normalize(sf::Vector2f(playerPosition.x - position_.x, playerPosition.y - position_.y));
    float radsToPlayer = atan2(normal.y, normal.x);
    sf::Vector2f bulletVelocity(cos(radsToPlayer) * 500.0f, sin(radsToPlayer) * 500.0f);
    if (!enrage_) scene_->AddGameObject(new EnemyBullet(*playerManager_, *map_, position_, bulletVelocity, 5.0f, sf::Color::Red, 1));
    bulletVelocity = sf::Vector2f(cos(radsToPlayer - (Math::PI() / 8.0f)), sin(radsToPlayer - (Math::PI() / 8.0f)));
    scene_->AddGameObject(new EnemyBullet(*playerManager_, *map_, position_, bulletVelocity * 500.0f, 5.0f, sf::Color::Red, 1));
    bulletVelocity = sf::Vector2f(cos(radsToPlayer + (Math::PI() / 8.0f)), sin(radsToPlayer + (Math::PI() / 8.0f)));
    scene_->AddGameObject(new EnemyBullet(*playerManager_, *map_, position_, bulletVelocity * 500.0f, 5.0f, sf::Color::Red, 1));

    if (enrage_)
    {
        int randRad = 5 - (int)(std::rand() / ((RAND_MAX + 1u) / 10));
        bulletVelocity = sf::Vector2f(cos(radsToPlayer + (Math::PI() / 8 / 5 * randRad)), sin(radsToPlayer + (Math::PI() / 8 / 5 * randRad)));
        scene_->AddGameObject(new EnemyBullet(*playerManager_, *map_, position_, bulletVelocity * 500.0f, 5.0f, sf::Color::Red, 1));
    }
}

void EnemyBoss::Bomb(float delta_time)
{
    nextBomb_ += delta_time;
    if (nextBomb_ >= 0.1f)
    {
        sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
        scene_->AddGameObject(new EnemyBomb(*playerManager_, playerPosition, sf::Vector2i(32 * 3, 32 * 3), 1.0f));
        if (enrage_)
        {
            sf::Vector2f bombPosition(playerPosition.x + 32 * (10 - (int)(std::rand() / ((RAND_MAX + 1u) / 21))), playerPosition.y + 32 * (10 - (int)(std::rand() / ((RAND_MAX + 1u) / 21))));
            scene_->AddGameObject(new EnemyBomb(*playerManager_, bombPosition, sf::Vector2i(32 * 3, 32 * 3), 1.0f));
        }
        nextBomb_ = 0.0f;
    }
    bombTimer_ += delta_time;
    if (bombTimer_ >= bombDone_)
    {
        bombTimer_ = 0.0f;
        nextBomb_ = 0.0f;
        currentAttack_ = shoot;
    }
}

void EnemyBoss::Dash(float delta_time)
{
    if (dashTimer_ >= dashTime_)
    {
        // LERP HERE
        position_ = Math::Lerp(position_, potentialDestinations_[currentKey_], delta_time * 2.0f);
        rect_.setPosition(position_);
        hpBar_->SetPosition(sf::Vector2f(position_.x, position_.y - imageHeight_));
        // SHOOT HERE
        shootTimer_ += delta_time;
        if (shootTimer_ >= 0.2f)
        {
            shootTimer_ = 0.0f;
            float bulletNum = 6.0f;
            if (enrage_) bulletNum = 10.0f;
            for (int i = 0; i < bulletNum; i++)
            {
                sf::Vector2f bulletVelocity(cos(2.0f * Math::PI() / bulletNum * i) * 500.0f, sin(2.0f * Math::PI() / bulletNum * i) * 500.0f);
                scene_->AddGameObject(new EnemyBullet(*playerManager_, *map_, position_, bulletVelocity, 5.0f, sf::Color::Red, 1));
            }
        }
        float distance = sqrt(pow(potentialDestinations_[currentKey_].x - position_.x, 2) + pow(potentialDestinations_[currentKey_].y - position_.y, 2));
        if (distance <= 3.0f)
        {
            position_ = potentialDestinations_[currentKey_];
            rect_.setPosition(position_);
            hpBar_->SetPosition(sf::Vector2f(position_.x, position_.y - imageHeight_));
            dashTimer_ = 0.0f;
            shootTimer_ = 0.0f;
            dashNum_--;
            if (dashNum_ <= 0) currentAttack_ = shoot;
            return;
        }
    }
    else if (dashTimer_ <= 0.0f) 
    {
        int destinationKey = std::rand() / ((RAND_MAX + 1u) / potentialDestinations_.size());
        int failsafe = 100;
        while (currentKey_ == destinationKey && failsafe > 0)
        {
            failsafe--;
            destinationKey = std::rand() / ((RAND_MAX + 1u) / potentialDestinations_.size());
        }
        currentKey_ = destinationKey;
        if (dashNum_ == 0)
        {
            if (enrage_) dashNum_ = 3;
            else dashNum_ = 1;
        }
        scene_->AddGameObject(new EnemyDash(position_, potentialDestinations_[currentKey_], 5*32, dashTime_));
    }
    dashTimer_ += delta_time;
}

void EnemyBoss::Laser(float delta_time)
{
    currentAttack_ = shoot;
    if (enrage_)
    {
        sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
        scene_->AddGameObject(new EnemyLaser(*playerManager_, playerPosition, sf::Vector2i(32*5, 32*100), 3.0f));
        scene_->AddGameObject(new EnemyLaser(*playerManager_, playerPosition, sf::Vector2i(32*100, 32*5), 3.0f));
        for (int i = 0; i < 2; i++)
        {
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x + 32*5 * 2 * i, playerPosition.y), sf::Vector2i(32*5, 32*100), 3.0f));
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x - 32*5 * 2 * i, playerPosition.y), sf::Vector2i(32*5, 32*100), 3.0f));
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x, playerPosition.y + 32*5 * 2 * i), sf::Vector2i(32*100, 32*5), 3.0f));
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x, playerPosition.y - 32*5 * 2 * i), sf::Vector2i(32*100, 32*5), 3.0f));
        }
        return;
    }

    int attackDirection = std::rand() / ((RAND_MAX + 1u) / 2);
    sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
    if (attackDirection == 0)
    {
        sf::Vector2i size(32*5, 32*100);
        scene_->AddGameObject(new EnemyLaser(*playerManager_, playerPosition, size, 3.0f));
        for (int x = 0; x < 2; x++)
        {
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x + size.x * 2 * x, playerPosition.y), size, 3.0f));
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x - size.x * 2 * x, playerPosition.y), size, 3.0f));
        }
    }
    else
    {
        sf::Vector2i size(32*100, 32*5);
        scene_->AddGameObject(new EnemyLaser(*playerManager_, playerPosition, size, 3.0f));
        for (int y = 0; y < 2; y++)
        {
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x, playerPosition.y + size.y * 2 * y), size, 3.0f));
            scene_->AddGameObject(new EnemyLaser(*playerManager_, sf::Vector2f(playerPosition.x, playerPosition.y - size.y * 2 * y), size, 3.0f));
        }
    }
}

void EnemyBoss::Nuke(float delta_time)
{
    sf::Vector2f playerPosition = playerManager_->GetPlayer()->GetPosition();
    scene_->AddGameObject(new EnemyBomb(*playerManager_, playerPosition, sf::Vector2i(32 * 50, 32 * 50), 5.0f));
    currentAttack_ = shoot;
}
#ifndef PLAYERSTATS_H_
#define PLAYERSTATS_H_

class PlayerStats
{
public:
    void Reset();

    void SetExperience(int experience);
    int GetExperience() const;
    void SetMaxExperience(int max_experience);
    int GetMaxExperience() const;
    void SetLevel(int level);
    int GetLevel() const;
    void SetHP(int hp);
    int GetHP() const;
    void SetMaxHP(int max_hp);
    int GetMaxHP() const;
    void SetDamage(int damage);
    int GetDamage() const;
    void SetPlayerSpeed(float player_speed);
    float GetPlayerSpeed() const;
    void SetBulletRange(float bullet_range);
    float GetBulletRange() const;
    void SetBulletSpeed(float bullet_speed);
    float GetBulletSpeed() const;
    void SetFireRate(float fire_rate);
    int GetFireRate() const;

private:
    int experience_{0};
    int max_experience_{10};
    int level_{1};
    int hp_{3};
    int max_hp_{3};
    int damage_{1};
    float player_speed_{300.0f};
    float bullet_range_{1.0f};
    float bullet_speed_{500.0f};
    float fire_rate_{1};
};

#endif
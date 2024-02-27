#include "PlayerStats.h"

void PlayerStats::Reset()
{
    experience_ = 0;
    max_experience_ = 10;
    level_ = 1;
    hp_ = 3;
    max_hp_ = 3;
    damage_ = 1;
    bullet_range_ = 1.0f;
    bullet_speed_ = 500.0f;
    player_speed_ = 300.0f;
}

void PlayerStats::SetExperience(int experience) {experience_ = experience;}
int PlayerStats::GetExperience() const {return experience_;}
void PlayerStats::SetMaxExperience(int max_experience) {max_experience_ = max_experience;}
int PlayerStats::GetMaxExperience() const {return max_experience_;}
void PlayerStats::SetLevel(int level) {level_ = level;}
int PlayerStats::GetLevel() const {return level_;}
void PlayerStats::SetHP(int hp) {hp_ = hp;}
int PlayerStats::GetHP() const {return hp_;}
void PlayerStats::SetMaxHP(int max_hp) {max_hp_ = max_hp;}
int PlayerStats::GetMaxHP() const {return max_hp_;}
void PlayerStats::SetDamage(int damage) {damage_ = damage;}
int PlayerStats::GetDamage() const {return damage_;}
void PlayerStats::SetPlayerSpeed(float speed) {player_speed_ = speed;}
float PlayerStats::GetPlayerSpeed() const {return player_speed_;}
void PlayerStats::SetBulletRange(float range) {bullet_range_ = range;}
float PlayerStats::GetBulletRange() const {return bullet_range_;}
void PlayerStats::SetBulletSpeed(float bullet_speed) {bullet_speed_ = bullet_speed;}
float PlayerStats::GetBulletSpeed() const {return bullet_speed_;}
void PlayerStats::SetFireRate(float fire_rate) {fire_rate_ = fire_rate;}
int PlayerStats::GetFireRate() const {return fire_rate_;}
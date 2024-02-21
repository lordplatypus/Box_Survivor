#ifndef CHALLENGE_H_
#define CHALLENGE_H_
#include "GameObject.h"
#include "PlayerManager.h"
#include "Staircase.h"

class Challenge : public GameObject
{
public:
    Challenge();
    virtual ~Challenge();
    virtual void Init(const std::string& name, const std::string& challenge_text, 
                      PlayerManager* player_manager, Staircase* staircase); // CALL THIS IN CONSTRUCTOR

private:
    virtual void ChallengeUpdate() = 0;

public:
    virtual void Update(float delta_time) override;

    void SetChallengeText(const std::string& challenge_text);
    const std::string& GetChallengeText() const;

protected:
    std::string challenge_text_{""};
    PlayerManager* player_manager_{nullptr};
    Staircase* staircase_{nullptr};
};

#endif
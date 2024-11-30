#pragma once

#include "Core.h"
#include "Amulet.h"


class ActionHandler
{
public:
    // Outside of combat actions
    template <typename Room>
    void Attack(std::string (Room::*aEnemyFunc)(), Room& aRoomObj); // Call and pass in the Enemy1 or Enemy2 overridden functons as a first parameter, and the room object as a second parameter to attack and solve the puzzle
    void Rest(); // Call to replenish your mana and age a year
    void Repair(); // Call to repair your amulet and age a year

    // Inside of combat actions
    Amulet ActivateAmulet(int aLineAmount); // Call within a new scope to make everything in the scope ignore mana cost. The parameter is the amount of lines used in the scope

    // Internal
    void SetGameState(GameState* aState) {mp_state = aState;};
private:
    GameState* mp_state;
};

#include "Actions.cpp"
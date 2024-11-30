#pragma once

#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <set>
#include <any>
#include <vector>
#include <cstdint>
#include <typeinfo>
#include <cstring>

// Constants
const int cStartingAge = 20;
const int32_t cManaGainFromAge = 50;
const int32_t cStartingMana = 100;
const int cAmuletBreakIntervalLines = 10;
const int cMaxAmuletBrokenChars = 25;

// Global variables
inline int32_t g_manaCounter = 0;

struct GameState
{
    int age;
    int amuletWear;
    int32_t* p_manaCounter;
    int32_t maxMana() const 
    {
        return cStartingMana + ( (age-cStartingAge) * cManaGainFromAge );
    }
    std::string brokenCharacters;
    bool amuletUsedAlready;
};

#include "ManaClasses.h"
#include "Utilities.h"
#include "Actions.h"


class Encounter 
{
private:
    GameState* mp_state;
public:

    ActionHandler Actions;
    Encounter() 
    {
        std::cout << std::endl;
        mp_state = new GameState();

        mp_state->age = cStartingAge;
        g_manaCounter = cStartingMana;
        mp_state->p_manaCounter = &g_manaCounter;
        mp_state->amuletWear = 0;
        mp_state->brokenCharacters = "";

        Actions.SetGameState(mp_state);

        SystemUtilities::flavorPrint("You push open the creaking door to enter a new room full of enemies.");
        std::cout << std::endl;
    }

    void LoadAdventure(int aAge, int32_t aManaLeft, int aAmuletWear, std::string aBrokenCharacters)
    {
        if(aAge == 0)
        {
            return;
        }
        
        mp_state->age = aAge;
        g_manaCounter = aManaLeft;
        mp_state->amuletWear = aAmuletWear;
        mp_state->brokenCharacters = aBrokenCharacters;
        SystemUtilities::printState(mp_state);
    }

    virtual ~Encounter() 
    {
        delete mp_state;
    }

    template <typename T>
    T* Cast() 
    {
        size_t size = sizeof(T);

        g_manaCounter -= size;

        T* obj = static_cast<T*>(malloc(size));

        if (!obj) throw std::runtime_error("Memory allocation failed!");
        new (obj) T();

        return obj;
    }

    template <typename T>
    void Cast()
    {
        g_manaCounter -= sizeof(T);
    }
    void Cast(std::any obj)
    {
        g_manaCounter -= sizeof(obj);
    }

    virtual std::string Enemy1() = 0;
    virtual std::string Enemy2() = 0;
};
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
#include <algorithm>
#include <numeric>
#include <memory>
#include <utility>

// Constants
const int cStartingAge = 20;
const int32_t cManaGainFromAge = 250;
const int32_t cStartingMana = 500;
const int cAmuletBreakIntervalLines = 10;
const int cMaxAmuletBrokenChars = 25;

const bool DebugLogManaUsage = false;

// Global variables
inline int32_t g_manaCounter = 0;
static void UseMana(int aBitsUsed, std::string aReason = "undefined")
{
    g_manaCounter -= aBitsUsed*8; // to byte
    if(DebugLogManaUsage)
    {
        std::cout << "Mana used: " << aBitsUsed*8 << " by " << aReason << std::endl;
    }
} 

// input
inline std::vector<std::string> lines;

struct GameState
{
    int roomId;
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

#include "BaseTheme.h"
#include "HistorianTheme.h"
HistorianTheme* theme = new HistorianTheme();

#include "Actions.h"
ActionHandler* Actions = new ActionHandler();

#include "ManaClasses.h"
#include "Utilities.h"


class Encounter 
{
private:
    GameState* mp_state;
public:

    Encounter(int aRoomId) 
    {
        std::cout << std::endl;
        mp_state = new GameState();

        mp_state->roomId = aRoomId;
        mp_state->age = cStartingAge;
        g_manaCounter = cStartingMana;
        mp_state->p_manaCounter = &g_manaCounter;
        mp_state->amuletWear = 0;
        mp_state->brokenCharacters = "";

        Actions->SetGameState(mp_state);

        theme->StartDay(aRoomId);
    }

    void LoadAdventure(int aAge, int32_t aManaLeft, int aAmuletWear, std::string aBrokenCharacters)
    {
        if(aAge != 0)
        {
            mp_state->age = aAge;
            g_manaCounter = aManaLeft;
            mp_state->amuletWear = aAmuletWear;
            mp_state->brokenCharacters = aBrokenCharacters;
        }
        
        theme->printState(mp_state);
    }

    virtual ~Encounter() 
    {
        delete mp_state;
    }

    template <typename T>
    T* Cast() 
    {
        size_t size = sizeof(T);

        UseMana(size, typeid(T).name());

        T* obj = static_cast<T*>(malloc(size));

        if (!obj) throw std::runtime_error("Memory allocation failed!");
        new (obj) T();

        return obj;
    }

    void Cast(int size, std::string name = "manual cast")
    {
        UseMana(size, name);
    }
    void Cast(long long unsigned int size, std::string name = "manual cast")
    {
        UseMana(size, name);
    }
    template <typename T>
    T Cast(const T &obj)
    {
        size_t size = 0;

        // Check if the object is a std::vector
        if constexpr (std::is_same_v<T, std::vector<typename T::value_type>>)
        {
            size = obj.size() * sizeof(typename T::value_type); // Compute content size
        }
        // check if the object is a std::string
        else if constexpr (std::is_same_v<T, std::string>)
        {
            size = obj.size() + 1 + sizeof(T); // Compute content size plus null terminator
        }
        else
        {
            size = sizeof(T);
        }

        UseMana(size, typeid(T).name());

        return obj;
    }

    virtual std::string Part1() = 0;
    virtual std::string Part2() = 0;
};
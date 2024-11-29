#ifndef RPG_CORE_H
#define RPG_CORE_H

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <set>
#include <any>
#include <vector>
#include <cstdint>
#include <typeinfo>
#include <cstring>
#include <chrono>


inline int32_t g_manaCounter = 0;

#include "ManaClasses.h"

//\033[<color>m
//https://jakob-bagterp.github.io/colorist-for-python/ansi-escape-codes/standard-16-colors/#bright-colors_2

void* my_malloc(size_t size)
{
    g_manaCounter -= size;
    void *p = malloc(size);
    return p;
}
#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)

void flavorPrint(std::string text)
{
    std::cout << "\x1b[0m * " << text << "\x1b[97m\n";
}

class Encounter 
{
protected:

    const int cStartingAge = 20;
    const int32_t cManaGainFromAge = 50;
    const int32_t cStartingMana = 100;

    int m_age;
    int m_amuletWear;
    bool m_amuletActive = false;

public:

    Encounter() 
    {
        m_age = cStartingAge;
        g_manaCounter = cStartingMana;
        m_amuletWear = 0;
        flavorPrint("You push open the creaking door to enter a new room full of enemies.");
    }

    void LoadAdventure(int aAge, int32_t aManaLeft, int aAmuletWear)
    {
        if(!aAge && !aManaLeft && !aAmuletWear)
        {
            return;
        }
        
        m_age = aAge;
        g_manaCounter = aManaLeft;
        m_amuletWear = aAmuletWear;
        printState();
    }

    virtual ~Encounter() {}

    int32_t maxMana() const 
    {
        return cStartingMana + ( (m_age-cStartingAge) * cManaGainFromAge );
    }

    void printState() const 
    {
        std::cout << std::endl
                  << "\x1b[97m- Age: \x1b[95m" << m_age << "\x1b[97m years" <<  std::endl
                  << "\x1b[97m- Mana: \x1b[94m" << g_manaCounter << "\x1b[97m / \x1b[34m" << maxMana() << std::endl
                  << "\x1b[97m- Amulet Wear: \x1b[33m" << m_amuletWear << "\x1b[97m lines"  << std::endl
                  << "\x1b[0m";
    }

    template <typename T>
    T* Cast() 
    {
        size_t size = sizeof(T);

        if (!m_amuletActive) {
            g_manaCounter -= size;
        }
        
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

    void ActivateAmulet()
    {
        m_amuletActive = true;
    }

    void DeactivateAmulet(int aUsedLines)
    {
        m_amuletWear += aUsedLines;
        m_amuletActive = true;
    }

    virtual std::string Enemy1() = 0;
    virtual std::string Enemy2() = 0;

    template <typename T>
    void Fight(std::string (T::*func)(), T& obj) 
    {
        const int32_t cCachedMana = g_manaCounter;
        const auto cStartTime = std::chrono::high_resolution_clock::now();

        const std::string damage = (obj.*func)();

        const double cRuntime = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - cStartTime).count();
        const int32_t cManaUsed = cCachedMana - g_manaCounter;

        std::stringstream mana_ss;
        std::cout << std::endl;
        mana_ss << "You conjure a spell in \x1b[95m" << cRuntime << "\x1b[0m milliseconds, consuming \x1b[94m" << cManaUsed << "\x1b[0m mana.";
        flavorPrint(mana_ss.str());

        std::stringstream dmg_ss;
        if(g_manaCounter > 0)
        {
            dmg_ss << "Your blow lands true, inflicting \x1b[91m" << damage << "\x1b[0m damage on your enemy!";
            flavorPrint(dmg_ss.str());
            printState();
        }
        else
        {
            dmg_ss << "Drained beyond your limits (\x1b[94m"<<-g_manaCounter<< "\x1b[97m mana), you faint as your spell unleashes \x1b[91m" << damage << "\x1b[0m damage upon your enemies.";
            flavorPrint(dmg_ss.str());
            flavorPrint("Your adventure ends here.");
        }
    }

    void Rest()
    {
        flavorPrint("You sit down to rest, allowing your mana to replenish. The world grows a little heavier as time passes as the weight of age settles upon you.");
        m_age++;
        g_manaCounter = maxMana();
        printState();
    }

    void RepairAmulet()
    {
        flavorPrint("You take a moment to repair your amulet, restoring its power but feeling the passage of time weigh heavier upon you.");
        m_amuletWear = 0;
        printState();
    }
};

#endif // RPG_CORE_H
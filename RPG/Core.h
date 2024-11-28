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


inline size_t g_manaCounter = 0;

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
    const size_t cManaGainFromAge = 50;
    const size_t cStartingMana = 150;

    int m_age;
    int m_amuletWear;
    bool m_amuletActive = false;

public:

    Encounter() 
    {
        m_age = cStartingAge;
        g_manaCounter = cStartingMana;
        m_amuletWear = 0;
        flavorPrint("You push open the creaking door to enter a new room full of enemies");
    }

    void LoadAdventure(int aAge, size_t aManaLeft, int aAmuletWear)
    {
        m_age = aAge;
        g_manaCounter = aManaLeft;
        m_amuletWear = aAmuletWear;
        printState();
    }

    virtual ~Encounter() {}

    size_t maxMana() const 
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
        const size_t cCachedMana = g_manaCounter;

        const std::string damage = (obj.*func)();

        const size_t cManaUsed = cCachedMana - g_manaCounter;

        std::stringstream mana_ss;
        std::cout << std::endl;
        mana_ss << "You conjure a spell, consuming \x1b[94m" << cManaUsed << "\x1b[0m mana.";
        flavorPrint(mana_ss.str());

        std::stringstream dmg_ss;
        dmg_ss << "Your blow lands true, inflicting \x1b[91m" << damage << "\x1b[0m damage on your enemy!";
        flavorPrint(dmg_ss.str());

        printState();
    }
};

#endif // RPG_CORE_H
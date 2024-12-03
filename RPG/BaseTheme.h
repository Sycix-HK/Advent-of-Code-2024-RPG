#pragma once

#include "Core.h"

#include <sstream>

static void flavorPrint(std::string text)
{
    std::cout << "\x1b[0m * " << text << "\x1b[97m\n";
}

class BaseTheme {
public:
    virtual ~BaseTheme() = default;

    virtual void printState(const GameState* apState) const 
    {
        std::cout << std::endl
                  << "\x1b[97m- Age: \x1b[95m" << apState->age << "\x1b[97m years" << std::endl
                  << "\x1b[97m- Mana: \x1b[94m" << g_manaCounter << "\x1b[97m / \x1b[34m" << apState->maxMana() << std::endl
                  << "\x1b[97m- Amulet Wear: \x1b[33m" << apState->amuletWear << "\x1b[97m lines" << std::endl
                  << "\x1b[0m- Characters broken out of amulet: \x1b[97m" << apState->brokenCharacters << std::endl
                  << "\x1b[0m" << std::endl;
    }

    virtual void StartDay(int aRoomId) const 
    {
        std::stringstream enter_ss;
        enter_ss << "You push open the creaking door to enter room "<< aRoomId <<", crawling with enemies.";
        flavorPrint(enter_ss.str());
    }

    virtual void MissingInput() const 
    {
        flavorPrint("The path ahead is shrouded in darkness; the map you sought is nowhere to be found.");
    }

    virtual void ManaUsed(double aRunTime, int aManaSpent) const
    {
        std::stringstream mana_ss;
        mana_ss << "You conjure a spell in \x1b[95m" << aRunTime << "\x1b[0m milliseconds, consuming \x1b[94m" << aManaSpent << "\x1b[0m mana.";
        flavorPrint(mana_ss.str());
    }

    virtual void DamageDealt(std::string aDamage) const
    {
        std::stringstream dmg_ss;
        dmg_ss << "Your blow lands true, inflicting \x1b[91m" << aDamage << "\x1b[0m damage on your enemy!";
        flavorPrint(dmg_ss.str());
    }

    virtual void DamageDealtNoMana(std::string aDamage, int aOverMana) const
    {
        std::stringstream dmg_ss;
        dmg_ss << "Drained beyond your limits (by \x1b[94m" << aOverMana << "\x1b[97m mana), you faint as your spell unleashes \x1b[91m" << aDamage << "\x1b[0m damage upon your enemies.";
        flavorPrint(dmg_ss.str());

        GameOver();
    }

    virtual void Rest() const 
    {
        flavorPrint("You sit down to rest, allowing your mana to replenish. The world grows a little heavier as the weight of age settles upon you.");
    }

    virtual void Repair() const
    {
        flavorPrint("You take a moment to repair your amulet, as the passage of time weigh heavier upon you.");
    }

    virtual void AmuletUsed(int aBlockedMana, int aEnduredLines) const
    {
        std::stringstream amulet_ss;
        amulet_ss << "You invoke your amulet, shielding \x1b[94m" << aBlockedMana << "\x1b[0m mana as it endures \x1b[33m" << aEnduredLines << "\x1b[0m lines of strain.";
        flavorPrint(amulet_ss.str());
    }

    virtual void AmuletUsedAgain()
    {
        flavorPrint("As you reach for the amulet again, it overheats, engulfing you in a surge of uncontrolled energy.");
        GameOver();
    }

    virtual void AmuletBrokenBeyondLimit()
    {
        std::stringstream max_ss;
        max_ss << "The amulet, strained beyond its limit of "<<cMaxAmuletBrokenChars<<" breaks, fractures completely, unleashing a torrent of magic that obliterates the entire dungeon.";
        flavorPrint(max_ss.str());
        GameOver();
    }

    virtual void AmuletBreaking(std::string aChars)
    {
        std::stringstream break_ss;
        break_ss << "As you glance at the amulet, you notice the character";
        break_ss << aChars;
        break_ss << " fractured under the strain, unusable until repaired.";
        flavorPrint(break_ss.str());
    }

    virtual void GameOver() const
    {
        flavorPrint("Your adventure ends here.");
        std::cout << std::endl;
        exit(0);
    }
};

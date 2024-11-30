#include "Actions.h"

#include "Core.h"
#include "Utilities.h"

#include <chrono>
#include <sstream>
#include <functional>

template <typename Room>
void ActionHandler::Attack(std::string (Room::*aEnemyFunc)(), Room& aRoomObj)
{
    mp_state->amuletUsedAlready = false;
    const int cCachedCharacterWear = mp_state->amuletWear / cAmuletBreakIntervalLines;

    const int32_t cCachedMana = g_manaCounter;
    const auto cStartTime = std::chrono::high_resolution_clock::now();

    const std::string damage = (aRoomObj.*aEnemyFunc)();

    const double cRuntime = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - cStartTime).count();
    const int32_t cManaUsed = cCachedMana - g_manaCounter;

    std::stringstream mana_ss;
    mana_ss << "You conjure a spell in \x1b[95m" << cRuntime << "\x1b[0m milliseconds, consuming \x1b[94m" << cManaUsed << "\x1b[0m mana.";
    SystemUtilities::flavorPrint(mana_ss.str());

    std::stringstream dmg_ss;
    if (g_manaCounter > 0)
    {
        dmg_ss << "Your blow lands true, inflicting \x1b[91m" << damage << "\x1b[0m damage on your enemy!";
        SystemUtilities::flavorPrint(dmg_ss.str());
    }
    else
    {
        dmg_ss << "Drained beyond your limits (\x1b[94m" << -g_manaCounter << "\x1b[97m mana), you faint as your spell unleashes \x1b[91m" << damage << "\x1b[0m damage upon your enemies.";
        SystemUtilities::flavorPrint(dmg_ss.str());
        SystemUtilities::flavorPrint("Your adventure ends here.");
        return;
    }

    const int cNowBrokenCharCount = (mp_state->amuletWear/cAmuletBreakIntervalLines)-cCachedCharacterWear;
    if(cNowBrokenCharCount != 0)
    {
        std::hash<std::string> hashFn;
        Amulet::BreakChars(cNowBrokenCharCount, &mp_state->brokenCharacters, static_cast<int>(hashFn(damage)));
    }

    SystemUtilities::printState(mp_state);
}

void ActionHandler::Rest()
{
    SystemUtilities::flavorPrint("You sit down to rest, allowing your mana to replenish. The world grows a little heavier as the weight of age settles upon you.");
    mp_state->age++;
    g_manaCounter = mp_state->maxMana();
    SystemUtilities::printState(mp_state);
}

void ActionHandler::Repair()
{
    SystemUtilities::flavorPrint("You take a moment to repair your amulet, as the passage of time weigh heavier upon you.");
    mp_state->amuletWear = 0;
    SystemUtilities::printState(mp_state);
}

[[nodiscard]] Amulet ActionHandler::ActivateAmulet(int aLineAmount)
{
    if(mp_state->amuletUsedAlready)
    {
        return Amulet::NonFunctionalAmulet(aLineAmount, &mp_state->amuletWear, &mp_state->brokenCharacters);
    }
    mp_state->amuletUsedAlready = true;
    return Amulet(aLineAmount, &mp_state->amuletWear, &mp_state->brokenCharacters);
}
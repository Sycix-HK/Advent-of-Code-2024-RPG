#include "Actions.h"

#include "Core.h"
#include "Utilities.h"

#include <chrono>
#include <sstream>
#include <functional>

template <typename Room>
void ActionHandler::Solve(std::string (Room::*aFunc)(), Room& aRoomObj)
{
    mp_state->amuletUsedAlready = false;
    const int cCachedCharacterWear = mp_state->amuletWear / cAmuletBreakIntervalLines;
    const int32_t cCachedMana = g_manaCounter;

    lines = AOCUtilities::ReadLines(mp_state->roomId);

    const auto cStartTime = std::chrono::high_resolution_clock::now();

    const std::string damage = (aRoomObj.*aFunc)();

    const double cRuntime = 
        std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - cStartTime).count();
    const int32_t cManaUsed = cCachedMana - g_manaCounter;

    theme->ManaUsed(cRuntime, cManaUsed);

    if (g_manaCounter > 0)
    {
        theme->DamageDealt(damage);
    }
    else
    {
        theme->DamageDealtNoMana(damage, -g_manaCounter);
        return;
    }

    const int cNowBrokenCharCount = (mp_state->amuletWear/cAmuletBreakIntervalLines)-cCachedCharacterWear;
    if(cNowBrokenCharCount != 0)
    {
        std::hash<std::string> hashFn;
        Amulet::BreakChars(cNowBrokenCharCount, &mp_state->brokenCharacters, static_cast<int>(hashFn(damage)));
    }

    theme->printState(mp_state);
}

void ActionHandler::Rest()
{
    mp_state->age++;
    g_manaCounter = mp_state->maxMana();

    theme->Rest();
    theme->printState(mp_state);
}

void ActionHandler::Repair()
{
    mp_state->amuletWear = 0;
    mp_state->brokenCharacters = "";

    theme->Repair();
    theme->printState(mp_state);
}

[[nodiscard]] std::unique_ptr<Amulet> ActionHandler::ActivateAmulet(int aLineAmount)
{
    if(mp_state->amuletUsedAlready)
    {
        theme->AmuletUsedAgain();
    }
    mp_state->amuletUsedAlready = true;
    return std::make_unique<Amulet>(aLineAmount, &mp_state->amuletWear, &mp_state->brokenCharacters);
}
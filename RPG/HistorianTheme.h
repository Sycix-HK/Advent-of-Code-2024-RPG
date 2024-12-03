#pragma once

#include "Core.h"
#include "BaseTheme.h"

class HistorianTheme : public BaseTheme
{
public:
    void printState(const GameState* apState) const override
    {
        std::cout << std::endl
                  << "\x1b[97m- Age: \x1b[95m" << apState->age << "\x1b[97m years" << std::endl
                  << "\x1b[97m- Energy: \x1b[94m" << g_manaCounter << "\x1b[97m / \x1b[34m" << apState->maxMana() << std::endl
                  << "\x1b[97m- Artifact Wear: \x1b[33m" << apState->amuletWear << "\x1b[97m lines" << std::endl
                  << "\x1b[0m- Clues damaged in Artifact: \x1b[97m" << apState->brokenCharacters << std::endl
                  << "\x1b[0m" << std::endl;
    }

    void StartDay(int aRoomId) const override
    {
        std::stringstream enter_ss;
        enter_ss << "You carefully push the door open to room "<< aRoomId <<", entering a chamber filled with dusty tomes and ancient scrolls.";
        flavorPrint(enter_ss.str());
    }

    void MissingInput() const override
    {
        flavorPrint("The archive is barren; the vital record is missing from its rightful place.");
    }

    void ManaUsed(double aRunTime, int aManaSpent) const override
    {
        std::stringstream energy_ss;
        energy_ss << "You decipher an ancient text in \x1b[95m" << aRunTime << "\x1b[0m milliseconds, expending \x1b[94m" << aManaSpent << "\x1b[0m energy.";
        flavorPrint(energy_ss.str());
    }

    void DamageDealt(std::string aDamage) const override
    {
        std::stringstream dmg_ss;
        dmg_ss << "You uncover a critical clue, unraveling \x1b[91m" << aDamage << "\x1b[0m layers of historical mystery.";
        flavorPrint(dmg_ss.str());
    }

    void DamageDealtNoMana(std::string aDamage, int aOverMana) const override
    {
        std::stringstream dmg_ss;
        dmg_ss << "Exhausted beyond measure (by \x1b[94m" << aOverMana << "\x1b[97m energy), you faint as the final clue reveals \x1b[91m" << aDamage << "\x1b[0m pieces of truth.";
        flavorPrint(dmg_ss.str());
        GameOver();
    }

    void Rest() const override
    {
        flavorPrint("You take a moment to recover, drawing on the strength of the room's historical resonance, growing wiser but older.");
    }

    void Repair() const override
    {
        flavorPrint("The artifact regains its stability as you restore it, though the effort leaves you feeling the passage of time.");
    }

    void AmuletUsed(int aBlockedMana, int aEnduredLines) const override
    {
        std::stringstream artifact_ss;
        artifact_ss << "You activate the artifact, shielding \x1b[94m" << aBlockedMana << "\x1b[0m energy as it endures \x1b[33m" << aEnduredLines << "\x1b[0m lines of strain.";
        flavorPrint(artifact_ss.str());
    }

    void AmuletUsedAgain() override
    {
        flavorPrint("You attempt to use the artifact again, but its ancient power spirals out of control");
    }

    void AmuletBrokenBeyondLimit() override
    {
        std::stringstream max_ss;
        max_ss << "The artifact, pushed beyond its limit of " << cMaxAmuletBrokenChars << ", fractures entirely, releasing a surge of energy that destroys everything in its wake.";
        flavorPrint(max_ss.str());
        GameOver();
    }

    void AmuletBreaking(std::string aChars) override
    {
        std::stringstream break_ss;
        break_ss << "A fragile part of the artifact fractures under strain, rendering the character" << aChars << "' unusable until repaired.";
        flavorPrint(break_ss.str());
    }

    void GameOver() const override
    {
        flavorPrint("Your quest to find the Chief Historian ends here.");
        std::cout << std::endl;
        exit(0);
    }
};

#define Amulet Artifact
#define ActivateAmulet ActivateArtifact
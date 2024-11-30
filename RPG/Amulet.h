#pragma once

#include "Core.h"

#include <sstream>

class Amulet
{
private: 
int m_lines;
int* mp_amuletWear;
int m_cached_manaCounter;
std::string* mp_brokenCharacters;
bool m_isFunctional = true; 
public:
    Amulet(int aLines, int* apAmuletWear, std::string* apBrokenCharacters)
    {
        m_lines = aLines;
        mp_amuletWear = apAmuletWear;
        m_cached_manaCounter = g_manaCounter;
        mp_brokenCharacters = apBrokenCharacters;
    }
    ~Amulet()
    {
        if (!m_isFunctional) {return;}
        const int cBlockedMana = m_cached_manaCounter - g_manaCounter;
        g_manaCounter = m_cached_manaCounter;
        *mp_amuletWear += m_lines;

        std::stringstream amulet_ss;
        amulet_ss << "You invoke your amulet, shielding \x1b[94m" << cBlockedMana << "\x1b[0m mana as it endures \x1b[33m" << m_lines << "\x1b[0m lines of strain.";
        SystemUtilities::flavorPrint(amulet_ss.str());
    }
    static Amulet NonFunctionalAmulet(int aLines, int* apAmuletWear, std::string* apBrokenCharacters)
    {
        Amulet am = Amulet(aLines,apAmuletWear,apBrokenCharacters);
        am.m_isFunctional = false;
        SystemUtilities::flavorPrint("As you reach for the amulet again, it overheats, engulfing you in a surge of uncontrolled energy.");
        SystemUtilities::flavorPrint("Your adventure ends here.");
        std::cout << std::endl;
        exit(0);
        return am;
    }
    static void BreakChars(int aAmount, std::string* apBrokenChars, int aSeed)
    {
        if (aAmount < 0) {return;}
        if(apBrokenChars->length() + aAmount > cMaxAmuletBrokenChars)
        {
            std::stringstream max_ss;
            max_ss << "The amulet, strained beyond its limit of "<<cMaxAmuletBrokenChars<<" breaks, fractures completely, unleashing a torrent of magic that obliterates the entire dungeon.";
            SystemUtilities::flavorPrint(max_ss.str());
            SystemUtilities::flavorPrint("Your adventure ends here.");
            std::cout << std::endl;
            return;
        }

        std::vector<char> charsToBreak;

        for (int i = 0; i < aAmount; ++i)
        {
            aSeed = abs(aSeed * 41);
            int k = 0;
            char c = static_cast<char>('A' + ((aSeed + i + k) % 26 + 26) % 26);
            while(apBrokenChars->find(c) != std::string::npos)
            {
                k++;
                c = static_cast<char>(aSeed + i+k);
            }
            charsToBreak.push_back(c);
            apBrokenChars->push_back(c);
        }

        std::stringstream break_ss;
        break_ss << "As you glance at the amulet, you notice the character";
        if(aAmount == 1)
        {
            break_ss << " '\x1b[91m" << charsToBreak[0] << "\x1b[0m'";
        }
        else
        {
            break_ss << "s ";
            for(int i =0; i < aAmount-2; ++i)
            {
                break_ss << "'\x1b[91m" << charsToBreak[i] << "\x1b[0m', ";
            }
            break_ss << "'\x1b[91m" << charsToBreak[aAmount-2] << "\x1b[0m' and '\x1b[91m" << charsToBreak[aAmount-1] << "\x1b[0m'";
        }

        break_ss << " fractured under the strain, unusable until repaired.";
        SystemUtilities::flavorPrint(break_ss.str());
    }
};
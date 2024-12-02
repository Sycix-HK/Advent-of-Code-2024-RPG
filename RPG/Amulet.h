#pragma once

#include "Core.h"

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

    virtual ~Amulet()
    {
        if (!m_isFunctional) {return;}
        const int cBlockedMana = m_cached_manaCounter - g_manaCounter;
        g_manaCounter = m_cached_manaCounter;
        *mp_amuletWear += m_lines;

        theme->AmuletUsed(cBlockedMana, m_lines);
    }
    
    static void BreakChars(int aAmount, std::string* apBrokenChars, int aSeed)
    {
        if (aAmount < 0) {return;}
        if(apBrokenChars->length() + aAmount > cMaxAmuletBrokenChars)
        {
            theme->AmuletBrokenBeyondLimit();
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

        theme->AmuletBreaking(break_ss.str());
    }
};
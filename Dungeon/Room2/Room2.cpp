#include "../../RPG/Core.h"

class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}

    void levelSafenessLoop(const std::vector<std::string> aLevel, uint8_t& aLoopI, uint16_c& aThrowAwayInt) // returning with a bool would cost energy
    {
        aLoopI = 0;
        
        const int8_t diff = stoi(aLevel[1]) - stoi(aLevel[0]);
        if (diff == 0 || abs(diff) > 3)
        {
            return;
        }

        // store if we're increasing in msb instead of allocating a bool
        if (diff > 0)
        {
            aThrowAwayInt |= 0b1000000000000000; 
        }
        else
        {
            aThrowAwayInt &= 0b0111111111111111;
        }

        for (aLoopI = 2; aLoopI < aLevel.size(); ++aLoopI)
        {
            const int8_t diff = stoi(aLevel[aLoopI]) - stoi(aLevel[aLoopI-1]);
            if (diff == 0 || abs(diff) > 3)
            {
                return;
            }
            if(((aThrowAwayInt.Get() & 0b1000000000000000) && diff < 0) || 
              (!(aThrowAwayInt.Get() & 0b1000000000000000) && diff > 0))
            {
                return;
            }
        }
    }
    std::string Part1() override
    {
        uint16_c safeLevelCount = 0; // output
        uint8_t i = uint8_c(1); // loop index inside

        for (auto line = lines.begin(); line != lines.end(); ++line)
        {
            const std::vector<std::string> cSplitLine = AOCUtilities::split(*line, " "); // const cache, no energy
            levelSafenessLoop(cSplitLine, i, safeLevelCount); // only passing in already energy-handled variables, otherwise we cheat the system
            if (i == cSplitLine.size()) // safe since loop ended with no early returns
            {
                safeLevelCount++;
            }

        }

        return safeLevelCount & 0b0111111111111111;
    }                           

    std::string Part2() override
    {
        uint16_c safeLevelCount = 0; // output
        uint8_t i = uint8_c(1); // loop index inside

        uint8_t j = uint8_c(0);
        uint8_t k = uint8_c(0);

        // we need a storage for splitlines now that we're creating variations from it
        // declaring a string is 32 bytes + size, so we need to use a char* instead, which only stores its size
        char variedSplitLine[24];  // max 7 number with 2 digits and 7 spaces plus null terminator + a space + a byte safety (7*3+3)
        Cast(24, "char*"); // that's 24 bytes

        for (auto line = lines.begin(); line != lines.end(); ++line)
        {
            const std::vector<std::string> cSplitLine = AOCUtilities::split(*line, " "); // const cache, no energy
            levelSafenessLoop(cSplitLine, i, safeLevelCount); // only passing in already energy-handled variables, otherwise we cheat the system
            if (i == cSplitLine.size()) // safe since loop ended with no early returns
            {
                safeLevelCount++;
            }
            else
            {
                // Fire up the  ✨ Problem Dampener ✨

                std::strcpy( variedSplitLine, (*line).data() );
                for(j = 0; j < cSplitLine.size(); ++j) // foreach variation
                {
                    // build the variaton without allocating
                    std::strcpy( variedSplitLine, "" );
                    for(k = 0; k < cSplitLine.size(); ++k)
                    {
                        if (k == j) continue;

                        if(variedSplitLine[0] != '\0')
                        {
                            std::strcat(variedSplitLine, " ");
                        }
                        std::strcat(variedSplitLine, cSplitLine[k].data());
                    }

                    // signal the end of the char*, otherwise it's memory garbage and stoi tries parsing it later...
                    std::strcat(variedSplitLine, "\0");

                    
                    const std::vector<std::string> cVariedSplitLine = AOCUtilities::split(variedSplitLine, " "); // const cache, no energy
                    levelSafenessLoop(cVariedSplitLine, i, safeLevelCount);
                    if (i == cVariedSplitLine.size()) // safe since loop ended with no early returns
                    {
                        safeLevelCount++;
                        break;      
                    }
                }
            }

        }

        return safeLevelCount & 0b0111111111111111;
    }
};

int main()
{
    Room room( 2 );

    room.LoadAdventure
    (
        /*   Age: */ 20
      ,/* Energy: */ 340
,/*Artifact Wear: */ 0
,/* Broken Chars: */ ""
    );

    Actions->Solve(&Room::Part1, room);
    Actions->Solve(&Room::Part2, room);

    // 52 energy won't be enough for the next puzzle
    Actions->Rest();

    return 0;
}

/**********************************************************************************
 *                                                                                *
 *            ROOM 2: Red-Nosed Reindeer nuclear fusion/fission plant             *
 *                                                                                *
 ********************************************************************************* 

 * You carefully push the door open to room 2, entering a chamber filled with dusty tomes and ancient scrolls.

- Age: 20 years
- Energy: 340 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 1.2225 milliseconds, expending 40 energy.
 * You uncover a critical clue, unraveling 463 layers of historical mystery.

- Age: 20 years
- Energy: 300 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 4.6719 milliseconds, expending 248 energy.
 * You uncover a critical clue, unraveling 514 layers of historical mystery.

- Age: 20 years
- Energy: 52 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

 * You take a moment to recover, drawing on the strength of the room's historical resonance, growing wiser but older.

- Age: 21 years
- Energy: 750 / 750
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

*/
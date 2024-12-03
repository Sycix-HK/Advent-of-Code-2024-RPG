#include "../../RPG/Core.h"

#include <regex>

class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}
    std::string Part1() override
    {
        uint32_c outp = 0;
        const std::string combinedLines = std::accumulate(lines.begin(), lines.end(), std::string(""));

        { auto Artifact = Actions->ActivateArtifact(3);

            std::regex pattern(R"(mul\((\d+),(\d+)\))"); Cast(pattern); // 1
            Cast(sizeof(std::sregex_token_iterator), "regexiterator");
            for (std::sregex_iterator rit((combinedLines).begin(), (combinedLines).end(), pattern); rit != std::sregex_iterator(); ++rit) // 2
            {
                outp += stoi((*rit)[1].str()) * stoi((*rit)[2].str()); // 3
            }
        }

        return outp;
    }

    std::string Part2() override
    {
        uint32_t outp = uint32_c(0b10000000000000000000000000000000);
        const std::string combinedLines = std::accumulate(lines.begin(), lines.end(), std::string(""));

        { auto Artifact = Actions->ActivateArtifact(3);

            std::regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))"); Cast(pattern); // 1
            Cast(sizeof(std::sregex_token_iterator), "regexiterator");
            for (std::sregex_iterator rit((combinedLines).begin(), (combinedLines).end(), pattern); rit != std::sregex_iterator(); ++rit) // 2
            {
                // to avoid using lines in branches, we can store the do / don'ts in the
                // most significant bit of the output int and only use *some* ternary operators in a single line

                // enchanting table solution:
                outp=(((*rit)[0]).str()[0]=='d')?((((*rit)[0]).str()=="do()")?(outp|(1<<31)):(outp&~(1<<31)))
                :((outp&(1<<31))?(outp+(stoi((*rit)[1].str())*stoi((*rit)[2].str()))):(outp)); // 3

                /*/ semi-readable solution:
                const bool cIsInstruction = (((*rit)[0]).str()[0] == 'd');
                outp = (cIsInstruction) ? 
                // if instruction, store if we do or don't in a bit
                ((((*rit)[0]).str() == "do()") ? (outp | (1 << 31)) : (outp & ~(1 << 31)))
                : 
                // it's a mul(), so either do the multiplication or don't do anything
                ((outp & (1 << 31)) ? (outp + (stoi((*rit)[1].str()) * stoi((*rit)[2].str()))) : (outp)); //*/
            }
        }

        return std::to_string( outp & 0b01111111111111111111111111111111 );
    }
};

int main()
{
    Room room( 3 );

    room.LoadAdventure
    (
        /*   Age: */ 20
      ,/* Energy: */ 52
,/*Artifact Wear: */ 0
,/* Broken Chars: */ ""
    );

    Actions->Solve(&Room::Part1, room);

    // 20 energy won't be enough for the next puzzle
    Actions->Rest();
    
    Actions->Solve(&Room::Part2, room);

    return 0;
}

/**********************************************************************************
 *                                                                                *
 *                     ROOM 3: North Pole Toboggan Rental Shop                    *
 *                                                                                *
 **********************************************************************************

 * You carefully push the door open to room 3, entering a chamber filled with dusty tomes and ancient scrolls.

- Age: 20 years
- Energy: 52 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

 * You activate the artifact, shielding 1344 energy as it endures 3 lines of strain.
 * You decipher an ancient text in 2.0225 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 171183089 layers of historical mystery.

- Age: 20 years
- Energy: 20 / 500
- Artifact Wear: 3 lines
- Clues damaged in Artifact:

 * You take a moment to recover, drawing on the strength of the room's historical resonance, growing wiser but older.

- Age: 21 years
- Energy: 750 / 750
- Artifact Wear: 3 lines
- Clues damaged in Artifact:

 * You activate the artifact, shielding 1344 energy as it endures 3 lines of strain.
 * You decipher an ancient text in 2.6219 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 63866497 layers of historical mystery.

- Age: 21 years
- Energy: 718 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

*/
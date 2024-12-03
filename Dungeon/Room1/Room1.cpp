#include "../../RPG/Core.h"

class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}
    std::string Part1() override
    {
        uint32_c outp = 0;
        std::sort(lines.begin(), lines.end());

        // variables for finding the lowest right side value later
        uint32_c lowestValNow;
        std::vector<std::string>::iterator lowestRightSide; Cast(lowestRightSide);
        for (auto it_left = lines.begin(); it_left != lines.end(); ++it_left)
        {
            lowestValNow = std::numeric_limits<uint32_t>::max();

            // for the purposes of this challenge, we need to avoid making another vector,
            // so let's find the lowest right side value each time
            for (auto it_right = lines.begin(); it_right != lines.end(); ++it_right)
            {
                const int tempRightVal = stoi(AOCUtilities::split(*it_right,"   ")[1]); // just cache for readability, obviously droppable, so don't use energy
                if (tempRightVal < lowestValNow)
                {
                    lowestValNow = tempRightVal;
                    lowestRightSide = it_right;
                }
            }

            outp += abs(static_cast<int>(lowestValNow.Extract() - stoi(AOCUtilities::split(*it_left,"   ")[0])));

            // replace the line with a maxed out right side so its not the lowest anymore
            std::stringstream ss;
            ss << AOCUtilities::split(*lowestRightSide,"   ")[0] << "   " << "99999";
            *lowestRightSide = ss.str();
        }

        return outp;
    }

    std::string Part2() override
    {
        uint32_c outp = 0;
        for (auto it_left = lines.begin(); it_left != lines.end(); ++it_left)
        {
            const uint64_t cLeftVal = stoi(AOCUtilities::split(*it_left,"   ")[0]); // just cache, no Energy
            
            for (auto it_right = lines.begin(); it_right != lines.end(); ++it_right)
            {
                const uint64_t cRightVal = stoi(AOCUtilities::split(*it_right,"   ")[1]); // just cache, no Energy

                if (cLeftVal == cRightVal)
                {
                    outp += cLeftVal;
                }
            }
        }
        return outp;
    }
};

int main()
{
    Room room( 1 );

    room.LoadAdventure
    (
        /*   Age: */ 0
      ,/* Energy: */ 0
,/*Artifact Wear: */ 0
,/* Broken Chars: */ ""
    );

    Actions->Solve(&Room::Part1, room);
    Actions->Solve(&Room::Part2, room);

    return 0;
}

/**********************************************************************************
 *                                                                                *
 *                       ROOM 1: Chief Historian's office                         *
 *                                                                                *
 **********************************************************************************

 * You carefully push the door open to room 1, entering a chamber filled with dusty tomes and ancient scrolls.

- Age: 20 years
- Energy: 500 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 293.283 milliseconds, expending 128 energy.
 * You uncover a critical clue, unraveling 3714264 layers of historical mystery.

- Age: 20 years
- Energy: 372 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 290.623 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 18805872 layers of historical mystery.

- Age: 20 years
- Energy: 340 / 500
- Artifact Wear: 0 lines
- Clues damaged in Artifact:

*/
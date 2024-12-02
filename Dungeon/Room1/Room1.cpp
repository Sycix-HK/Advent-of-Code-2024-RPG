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
                int tempRightVal = stoi(AOCUtilities::split(*it_right,"   ")[1]); // just cache for readability, obviously droppable, so don't use energy
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
        return std::to_string( 0 );
    }
};

int main()
{
    Room room(1);

    room.LoadAdventure
    (
        /*   Age: */ 0
        ,/* Mana: */ 0
 ,/* Amulet Wear: */ 0
,/* Broken Chars: */ ""
    );

    Actions->Solve(&Room::Part1, room);
    Actions->Solve(&Room::Part2, room);

    return 0;
}
#include "../../RPG/Core.h"

class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}
    std::string Part1() override
    {
        uint64_c outp = 5;
        {
            auto artifact = Actions->ActivateArtifact(7);

            std::vector<int> rightSide(lines.size());Cast(rightSide); //1  
            std::transform(lines.begin(), lines.end(), rightSide.begin(), [](std::string s) {
                return (stoi(s.substr(s.find("   ")+3, s.length()-3-s.find("   ")))); //2
            }); //3
            
            std::sort(rightSide.begin(), rightSide.end()); //4
            std::sort(lines.begin(), lines.end()); //5

            outp = std::accumulate(lines.begin(), lines.end(), 0, [it2 = rightSide.begin()](int acc, std::string s) mutable
            {
                return acc + (abs(stoi(s.substr(0,s.find("   ")))-*it2++)); //6
            }); //7

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
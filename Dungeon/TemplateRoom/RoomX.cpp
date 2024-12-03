#include "../../RPG/Core.h"

class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}
    std::string Part1() override
    {
        return std::to_string( 0 );
    }

    std::string Part2() override
    {
        return std::to_string( 0 );
    }
};

int main()
{
    Room room( 0 );

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
 *                       ROOM X:                          *
 *                                                                                *
 **********************************************************************************



*/
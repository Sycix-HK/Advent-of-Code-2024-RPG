#include "../../RPG/Core.h"

class Room : public Encounter
{
public: 
    std::string Enemy1() override
    {
        return std::to_string( 0 );
    }

    std::string Enemy2() override
    {
        return std::to_string( 0 );
    }
};

int main()
{
    Room room;

    room.LoadAdventure
    (
        /*   Age: */ 0
        ,/* Mana: */ 0
 ,/* Amulet Wear: */ 0
,/* Broken Chars: */ ""
    );

    room.Actions.Attack(&Room::Enemy1, room);
    room.Actions.Rest();
    room.Actions.Attack(&Room::Enemy2, room);
    room.Actions.Repair();

    return 0;
}
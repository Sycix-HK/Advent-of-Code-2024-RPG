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
    );

    room.Fight(&Room::Enemy1, room);
    room.Fight(&Room::Enemy2, room);

    return 0;
}
#include "../../RPG/Core.h"

class Room : public Encounter
{
public: 
    std::string Enemy1() override
    {
        std::vector<uint8_c> v = {8, 54, 2, 4};
        float_c f = 1.2;
        float_c val = v[0] + f;
        return val;
    }

    std::string Enemy2() override
    {
        int64_c v = 555;
        int8_c v2 = 2;
        return std::to_string(v+v2);
    }
};

int main()
{
    Room room;

    room.LoadAdventure
    (
        /*   Age: */ 23
        ,/* Mana: */ 158
 ,/* Amulet Wear: */ 2
    );

    room.Fight(&Room::Enemy1, room);
    room.Fight(&Room::Enemy2, room);

    return 0;
}
#include "../../RPG/Core.h"

constexpr int directions[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};

class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}
    std::string Part1() override
    {
        uint16_c outp = 0;
        uint8_t dir = uint8_c(0);
        uint8_t pos[2] = {0,0}; Cast(1*2); // 1 byte 2 elements
        uint8_t ahead[2] = {0,0}; Cast(1*2); // 1 byte 2 elements
        
        for(int y = 0; y < lines.size(); ++y)
        {
            const std::string line = lines[y];
            for (int x = 0; x < line.size(); ++x)
            {
                if(line[x] == '^')
                {
                    pos[0] = x, pos[1] = y;
                    goto start_predict_path;
                }
            }
        }

        start_predict_path:;

        lines[pos[1]][pos[0]] = 'X'; 
        outp++;

        while(pos[0] < lines[0].size() && pos[1] < lines[0].size() && pos[0] > 0 && pos[1] > 0)
        {
            ahead[0] = (pos[0] + directions[dir][0]);
            ahead[1] = (pos[1] + directions[dir][1]);

            if(lines[ahead[1]][ahead[0]] == '#')
            {
                dir = ++dir % 4;
            }
            else 
            {
                if(lines[ahead[1]][ahead[0]] == '.')
                {
                    lines[ahead[1]][ahead[0]] = 'X';
                    outp++;
                }

                pos[0] = ahead[0], pos[1] = ahead[1];
            }
        }

        return outp;
    }

    void TryMapLoop(uint8_t& dir, uint8_t (&pos)[2], uint8_t (&ahead)[2], std::vector<std::string> map, uint16_c& toIncrement)
    {
        dir = 0;
        while(pos[0] < map[0].size()-1 && pos[1] < map[0].size()-1 && pos[0] > 0 && pos[1] > 0)
        {
            ahead[0] = (pos[0] + directions[dir][0]);
            ahead[1] = (pos[1] + directions[dir][1]);

            if(map[ahead[1]][ahead[0]] == '#')
            {
                dir = ++dir % 4;
            }
            else 
            {
                if(map[ahead[1]][ahead[0]] == dir)
                {
                    toIncrement++;
                    return;
                }
                else
                {
                    map[ahead[1]][ahead[0]] = dir;
                    pos[0] = ahead[0], pos[1] = ahead[1];
                }
            }
        }
    }

    std::string Part2() override
    {
        uint16_c outp = 0;
        uint8_t dir = uint8_c(0);
        uint8_t pos[2] = {0,0}; Cast(1*2); // 1 byte 2 elements
        uint8_t ahead[2] = {0,0}; Cast(1*2); // 1 byte 2 elements

        // I have to redeclare them so I can pass them into the function without it allocating again
        uint8_t dir_inside = uint8_c(0);
        uint8_t pos_inside[2] = {0,0}; Cast(1*2); // 1 byte 2 elements
        uint8_t ahead_inside[2] = {0,0}; Cast(1*2); // 1 byte 2 elements
        uint8_t startingPos[2] = {0,0}; Cast(1*2); // 1 byte 2 elements

        
        for(int y = 0; y < lines.size(); ++y)
        {
            const std::string line = lines[y];
            for (int x = 0; x < line.size(); ++x)
            {
                if(line[x] == '^')
                {
                    startingPos[0] = x, startingPos[1] = y;
                    pos[0] = x, pos[1] = y;
                    goto start_predict_path;
                }
            }
        }

        start_predict_path:;

        lines[pos[1]][pos[0]] = 'X'; 
        outp++;

        while(pos[0] < lines[0].size() && pos[1] < lines[0].size() && pos[0] > 0 && pos[1] > 0)
        {

            //std::cout << (int)(pos[0]) << " " << (int)(pos[1]) << std::endl;

            ahead[0] = (pos[0] + directions[dir][0]);
            ahead[1] = (pos[1] + directions[dir][1]);

            if(lines[ahead[1]][ahead[0]] == '#')
            {
                dir = ++dir % 4;
            }
            else 
            {
                if (lines[ahead[1]][ahead[0]] != 'X')
                {
                    lines[ahead[1]][ahead[0]] = '#';
                    TryMapLoop(dir_inside, pos_inside, ahead_inside, lines, outp);
                    lines[ahead[1]][ahead[0]] = 'X';
                } 
                pos_inside[0] = startingPos[0], pos_inside[1] = startingPos[1];
                pos[0] = ahead[0], pos[1] = ahead[1];
            }
        }

        return outp;
    }
};

int main()
{
    Room room( 6 );

    room.LoadAdventure
    (
        /*   Age: */ 21
      ,/* Energy: */ 638
,/*Artifact Wear: */ 6
,/* Broken Chars: */ ""
    );

    Actions->Solve(&Room::Part1, room);
    Actions->Solve(&Room::Part2, room);

    return 0;
}

/**********************************************************************************
 *                                                                                *
 *               ROOM 6: North Pole prototype suit manufacturing lab              *
 *                                                                                *
 **********************************************************************************

- Age: 21 years
- Energy: 638 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 0.0866 milliseconds, expending 56 energy.
 * You uncover a critical clue, unraveling 5534 layers of historical mystery.

- Age: 21 years
- Energy: 582 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 286.947 milliseconds, expending 112 energy.
 * You uncover a critical clue, unraveling 2262 layers of historical mystery.

- Age: 21 years
- Energy: 470 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

*/
#include "../../RPG/Core.h"

constexpr char p1_levels[4] = {'X', 'M', 'A', 'S'};
constexpr int p1_directions[8][2] = {{0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}}; //x,y
        
class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}

    void rec_tick_XMAS(uint8_t& progress, uint8_t& currentDirection, uint8_t Y, uint8_t X)
    {
        if(progress > 3)
        {
            return;
        }

        const int nextCoord[2] = { (X+p1_directions[currentDirection][0]), (Y+p1_directions[currentDirection][1]) }; 
        if(nextCoord[0] < 0 || nextCoord[0] >= lines[0].length() || nextCoord[1] < 0 || nextCoord[1] >= lines.size())
        {
            return;
        }

        const char& charThere = lines[nextCoord[1]][nextCoord[0]];
        if(charThere != p1_levels[progress])
        {
            return;
        }

        rec_tick_XMAS(++progress, currentDirection, nextCoord[1], nextCoord[0]);
    }

    std::string Part1() override
    {
        uint16_c outp = 0;

        uint8_t progressIndex = uint8_c(0);
        uint8_t currentDirection = uint8_c(0);
        uint8_t X = uint8_c(0);
        uint8_t Y = uint8_c(0);

        for (Y = 0; Y < lines.size(); ++Y)
        {
            const std::string line = lines[Y];
            for (X = 0; X < line.size(); ++X)
            {
                if(lines[Y][X] == 'X')
                {
                    // check 8 directions
                    for(currentDirection = 0; currentDirection < 8; ++currentDirection)
                    {
                        progressIndex = 1;
                        rec_tick_XMAS(progressIndex, currentDirection, Y, X);
                        if(progressIndex > 3)
                        {
                            outp++;
                        }
                    }
                }
            }
        }

        return outp;
    }

    std::string Part2() override
    {
        uint16_c outp = 0;

        uint8_t X = uint8_c(0);
        uint8_t Y = uint8_c(0);

        constexpr int totalValueOfValidCross = (int)'M'*2 + (int)'S'*2;

        for (Y = 1; Y < lines.size()-1; ++Y)
        {
            const std::string line = lines[Y];
            for (X = 1; X < line.size()-1; ++X)
            {
                if(lines[Y][X] == 'A')
                {
                    const int totalValueOfThisCross = lines[Y+1][X+1] + lines[Y+1][X-1] + lines[Y-1][X+1] + lines[Y-1][X-1];
                    if(totalValueOfValidCross == totalValueOfThisCross 
                        && lines[Y+1][X+1] != lines[Y-1][X-1])
                    {
                        outp++;
                    }
                }
            }
        }

        return outp;
    }
};

int main()
{
    Room room( 4 );

    room.LoadAdventure
    (
        /*   Age: */ 21
      ,/* Energy: */ 718
,/*Artifact Wear: */ 6
,/* Broken Chars: */ ""
    );

    Actions->Solve(&Room::Part1, room);
    Actions->Solve(&Room::Part2, room);

    return 0;
}

/**********************************************************************************
 *                                                                                *
 *                       ROOM 4: Ceres monitoring station                         *
 *                                                                                *
 **********************************************************************************

- Age: 21 years
- Energy: 718 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 0.5972 milliseconds, expending 48 energy.
 * You uncover a critical clue, unraveling 2344 layers of historical mystery.

- Age: 21 years
- Energy: 670 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 0.167 milliseconds, expending 32 energy.
 * You uncover a critical clue, unraveling 1815 layers of historical mystery.

- Age: 21 years
- Energy: 638 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

*/
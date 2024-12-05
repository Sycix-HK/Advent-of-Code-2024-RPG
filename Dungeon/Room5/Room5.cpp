#include "../../RPG/Core.h"

#include <cmath>

class Room : public Encounter
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}
    std::string Part1() override
    {
        uint16_c outp = 0;
        bool_c areWePastNumPoint = false;

        const std::vector<std::string> rules = AOCUtilities::splitIntoGroups(lines)[0];
        const std::vector<std::string> updates = AOCUtilities::splitIntoGroups(lines)[1];

        // for each line
        for(auto it_update = updates.begin(); it_update != updates.end(); ++it_update)
        {
            const std::vector<std::string> splitUpdate = AOCUtilities::split(*it_update, ",");
            // for each number in line
            for (auto it_num = (splitUpdate).begin(); it_num != (splitUpdate).end(); ++it_num)
            {
                const std::string num = (*it_num);
                // for each rule
                for(auto it_rule = rules.begin(); it_rule != rules.end(); ++it_rule)
                {
                    const std::string rule = (*it_rule);
                    if ((*it_num) == AOCUtilities::split(*it_rule, "|")[1])
                    {
                        areWePastNumPoint = false;
                        // for each number after our current one
                        for(auto it_numToCheck = (splitUpdate).begin(); it_numToCheck != (splitUpdate).end(); ++it_numToCheck)
                        {
                            if (*it_num == *it_numToCheck)
                            {
                                areWePastNumPoint = true;
                                continue;
                            }

                            if (*it_numToCheck == AOCUtilities::split(*it_rule, "|")[0])
                            {
                                // if we're before the point, we're good, rule passed
                                // if we're past the number and I find your number on the left, you're toast
                                if(areWePastNumPoint)
                                {
                                    // rule failed. use dark magic to skip adding this row's middle entirely
                                    // this saves allocating a bool or the iterator (iterators are free if as long as they are only used as a foreach)
                                    goto check_next_update_line;
                                }
                                else
                                {
                                    // rule passed, use dark magic to break out of here
                                    goto check_next_rule;
                                }
                            }
                        }
                    }

                    check_next_rule:;
                }
            }

            outp += std::stoi(splitUpdate[ ceil(splitUpdate.size()/2) ]);
            
            check_next_update_line:;
        }

        return outp;
    }

    std::string Part2() override
    {
        uint16_c outp = 0;
        bool_c areWePastNumPoint = false;
        bool_c badLine = false;

        const std::vector<std::string> rules = AOCUtilities::splitIntoGroups(lines)[0];
        const std::vector<std::string> updates = AOCUtilities::splitIntoGroups(lines)[1];

        std::vector<uint8_t> splitUpdate;
        splitUpdate.reserve(24);
        Cast( sizeof(splitUpdate) + 24*sizeof(uint8_t) ); // there's no way to not tank this. you have to have the sorted line somehow

        // for each line
        for(auto it_update = updates.begin(); it_update != updates.end(); ++it_update)
        {
            badLine = false;
            const std::vector<std::string> splitUpdateStrings = AOCUtilities::split(*it_update, ",");
            splitUpdate.clear();
            std::transform(splitUpdateStrings.begin(), splitUpdateStrings.end(), std::back_inserter(splitUpdate), [](const std::string& str){
                return std::stoi(str);
            });

            start_processing_line_at_existing_splitUpdate:;

            // for each number in line
            for (auto it_num = (splitUpdate).begin(); it_num != (splitUpdate).end(); ++it_num)
            {
                // for each rule
                for(auto it_rule = rules.begin(); it_rule != rules.end(); ++it_rule)
                {
                    const std::string rule = (*it_rule);
                    if (std::to_string(*it_num) == AOCUtilities::split(*it_rule, "|")[1])
                    {
                        areWePastNumPoint = false;
                        // for each number after our current one
                        for(auto it_numToCheck = (splitUpdate).begin(); it_numToCheck != (splitUpdate).end(); ++it_numToCheck)
                        {
                            if (*it_num == *it_numToCheck)
                            {
                                areWePastNumPoint = true;
                                continue;
                            }

                            if (std::to_string(*it_numToCheck) == AOCUtilities::split(*it_rule, "|")[0])
                            {
                                // if we're before the point, we're good, rule passed
                                // if we're past the number and I find your number on the left, you're toast
                                if(areWePastNumPoint)
                                {
                                    // rule failed
                                    badLine = true;

                                    // I am not crazy, I know he swapped those numbers!
                                    // Are you telling me the sleigh launch safety manual just happens to print like that? 
                                    // No, he orchestrated it! The Elf!
                                    
                                    std::swap(*it_num, *it_numToCheck);

                                    goto start_processing_line_at_existing_splitUpdate;
                                }
                                else
                                {
                                    goto check_next_rule;
                                }
                            }
                        }
                    }

                    check_next_rule:;
                }
            }

            if(badLine)
            {
                outp += (splitUpdate[ ceil(splitUpdate.size()/2) ]);
            }
        }

        return outp;
    }
};

int main()
{
    Room room( 5 );

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
 *                     ROOM 5: North Pole Printing Department                     *
 *                                                                                *
 **********************************************************************************

- Age: 21 years
- Energy: 638 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 525.139 milliseconds, expending 24 energy.
 * You uncover a critical clue, unraveling 4135 layers of historical mystery.

- Age: 21 years
- Energy: 614 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

 * You decipher an ancient text in 8174.2 milliseconds, expending 416 energy.
 * You uncover a critical clue, unraveling 5285 layers of historical mystery.

- Age: 21 years
- Energy: 198 / 750
- Artifact Wear: 6 lines
- Clues damaged in Artifact:

*/
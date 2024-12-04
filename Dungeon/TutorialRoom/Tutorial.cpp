#include "../../RPG/Core.h"

/**********************************************************************************
 *                                                                                *
 *                               ROOM 0: Tutorial                                 *
 *                                                                                *
 **********************************************************************************

 * You step foot into the dungeon, the air heavy with the weight of forgotten secrets.

 // This is a more challenging way to solve Advent of Code puzzles.
 // I suggest reading this file line by line from top to bottom
 // You have a character sheet that tells you about your journey's state:
 
    - Age: 20 years                 <-- Your age is essentially your score, the lower the better.
    - Energy: 500 / 500             <-- As you allocate memory in code, your energy drains. Each bit is a point of energy.
    - Artifact Wear: 0 lines        <-- You have a special item that can negate the next few lines from using energy within a scope.
    - Clues damaged in Artifact:    <-- As you use your artifact, it breaks characters out of the artifact's scope.

 // Let's see what it looks like in practice

*/

class Room : public Encounter // Each AOC Day is a "Room", and they derive from Encounter that automatically handles the game logic
{
public: 
    Room(int aRoomId) : Encounter(aRoomId){}
    std::string Part1() override
    { /*⭐*/
        // The room automatically reads your input.txt if it's placed in the same folder as this file.
        /* Your input file is called */ lines; /*, and it's an */ std::vector<std::string> type;

        for( auto it = lines.begin(); it != lines.end(); ++it )
        {
            // This doesn't drain your energy, as it's unavoidable. Constexpressions and readability purposed variables are also free
            constexpr int EnergyFree = 0;
            const int ReadabilityOnlyVar = stoi(*it); // You could just call stoi every single time this would be used, so there's no point
            // However, most variables have to be energy managed manually.
            // There's a couple of ways to do this:
            uint8_c way1 = 0;  // Types that end in a " _c " instead of " _t " are my custom types to make life easier.
                               // These types are automatically energy managed upon construction. 
                               // You can convert them back to their _t value any time using the .get() method
            uint8_t way2 = uint8_c(0); // You can also immediately use them as their original value type, it's still energy-managed.
            uint8_t way3; Cast(way3); // This is the main way for non-numeric variables, it takes the object's sizeof()
                                      // It's named cast after casting a spell, not casting to a different type
            uint8_t way4; Cast(1 /*(size in bytes)*/); // You can also use this if you certainly know the size of the object, an uint8_t is 1 byte, which is 8 bits of energy.
        
            // be careful declaring variables inside loops, you don't gain energy back when they are deconstructed at the end of the scope!
        }

        // When you're done writing your logic, you can return with the solution
        return std::to_string( 123 ); /*
           * You uncover a critical clue, unraveling 123 layers of historical mystery.
*/  }

    // You may create new funtions, but both their parameters and their return values have to be energy managed
    std::string HelperFunction(uint32_t& parameterRef)
    {
        if(parameterRef == 0)
        {
            Cast(sizeof(std::string)+1); // Careful with strings though, their size is 32 bytes + each character inside them is 1 byte, including the null terminator!
            return "";
        }

        std::string outp = std::to_string(parameterRef);
        
        // You can also use the Cast's return value, it comes back with the object you passed into it
        return Cast(outp);
    }

    std::string Part2() override
    { /*⭐⭐*/
        // now calling the function, the return value is energy managed, but the parameters aren't yet
        uint32_t param = uint32_c(0);
        std::string result = HelperFunction(param);

        // At times where allocating way too much memory is unavoidable, you can use your special item: the Artifact
        // While you're using the artifact, you're on a line-constraint instead of a memory constraint.
        // To use it, you first have to create it's own scope, then use the ActivateArtifact() action
        {
            auto Artifact = Actions->ActivateArtifact(11 /*(lines in the scope, fill it in later)*/);
            // Now anything in this scope is prevented from using energy. 
            // As the artifact object leaves this scope, it gets destroyed, and the destructor sets back the energy depletion again.
            // I still recommend managing them, since the Artifact will tell you how much energy it blocked, but it's not necessary
            
            for(uint8_c i = 0; i < 70; ++i) // loops count as lines, so line 1
            {
                constexpr char toAdd = ' '; // readability lines don't count
                result += toAdd; // line 2
                std::vector<std::string> tempVector; Cast(tempVector); // line 3 for declaration, and Cast/energy management doesn't count
                std::transform(lines.begin(), lines.end(), std::back_inserter(tempVector), [](){
                    return (lines); // line 4
                }); // line 5, the transform call itself counts

                // If you call HelperFunction here, the lines have to be counted
                std::string myString = HelperFunction(param); // it has 5 lines, so 5+5 = 10 lines so far

                // Be careful, you cannot keep variables as they exit the scope, so you need to cache your values to outside variables
                result = myString; // line 11
            }
            /* So we counted 11 lines total in the scope. Now we can pass that number back in Actions->ActivateArtifact()
            // Every 10 lines of strain on the Artifact will break a character out of it.

              * A fragile part of the artifact fractures under strain, rendering the character M unusable until repaired.

            // The removed character will be random, but deterministic, where the seed will be your puzzle solution.
            // Up to 25 characters can be removed.
            // The removed characters cannot be used *inside the artifact's scope*. Variables you named don't count. Aliasing is not allowed 
            // For example, after M is removed, myString is still fine, but std::transform is now unusable inside Artifact scopes. 
*/      }

        // Let's move on to "out of puzzle" actions below
        return result;
    }
};

int main()
{
    // Here we have to instantiate the room. Pass the room's index into the constructor
    Room room( 0 );

    // Here you can load a character sheet from the previous encounter. Calling it with 0 age will start a new one.
    // You start at age 20, with 500 mana, and you gain +250 max mana per age.
    room.LoadAdventure
    (
        /*   Age: */ 0
      ,/* Energy: */ 0
,/*Artifact Wear: */ 0
,/* Broken Chars: */ ""
    );

    // Calling hese actions will output part 1 and part 2
    Actions->Solve(&Room::Part1, room);
    Actions->Solve(&Room::Part2, room);

    // You may call other actions here as well. Calling these will age you a year.
    // You may only call them before, after or between solutions.

    // The rest action will replenish your Energy to full
    Actions->Rest();

    // The repair action will repair the Artifact and clear all broken characters from it
    Actions->Repair();
    
    // Good luck, adventurer, and may the echoes of history guide you!
    return 0;
}

/**********************************************************************************
 *                                                                                *
 *                                END OF TUTORIAL                                 *
 *                                                                                *
 *********************************************************************************/
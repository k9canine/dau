//---------------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------------
#include "levels.h"
#include "utils.h"

#include <ctime>
#include <cstdlib>
// stores constants for the probability of a meteor for any given space

float level1 = 0.33333f;
float level2 = 0.4f;
float level3 = 0.5f;
float level4 = 0.66667f;

std::vector<int> generateArray(float level)
{
    std::vector<int> array;
    srand(time(0));

    float indivMeteorProb = level / 4;
    float noMeteorProb = 1 - level;

    for (int i = 0; i < METEOR_COLUMNS; i++)
    {                                            // random number generator
        float random = (float)rand() / RAND_MAX; // random value between 0 and 1

        if (random < noMeteorProb)
        {
            array.emplace_back(0); // no meteor
        }
        else if (random < noMeteorProb + 1 * indivMeteorProb)
        {
            array.emplace_back(1); // meteor 1
        }
        else if (random < noMeteorProb + 2 * indivMeteorProb)
        {
            array.emplace_back(2); // meteor 2
        }
        else if (random < noMeteorProb + 3 * indivMeteorProb)
        {
            array.emplace_back(3); // meteor 3
        }
        else
        {
            array.emplace_back(4); // meteor 4
        }
    }

    return array;
}
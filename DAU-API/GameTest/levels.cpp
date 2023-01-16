//---------------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------------
#include "levels.h"
#include "utils.h"

#include <ctime>
#include <cstdlib>
// stores constants for the probability of a meteor for any given space

int level1 = 1;
int level2 = 2;
int level3 = 3;
int level4 = 4;

float level1value = 0.2f;
float level2value = 0.333f;
float level3value = 0.4f;
float level4value = 0.5f;

std::vector<int> generateArray(int levelNum)
{
    float level;
    switch (levelNum)
    {
    case 1:
    {
        level = level1value;
        break;
    }
    case 2:
    {
        level = level2value;
        break;
    }
    case 3:
    {
        level = level3value;
        break;
    }
    case 4:
    {
        level = level4value;
        break;
    }
    default:
    {
        break;
    }
    }
    std::vector<int> array;
    srand(time(NULL));

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
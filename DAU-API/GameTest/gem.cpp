//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "gem.h"
#include "utils.h"

// sets the position of the gem
void setGem(CSimpleSprite *gem)
{
    // generate a random spot on the board
    int totalBoxes = METEOR_COLUMNS * METEOR_ROWS;
    int boxNumber = 0;
    int x, y; // the coordinates of the gem in the 2D array that is 11 x 8 (same as meteor 2D array)

    srand(time(NULL));
    float random = (float)rand() / RAND_MAX; // random value between 0 and 1
    float perBoxProbability = 1.0f / totalBoxes;

    for (int i = 0; i < totalBoxes; i++)
    {
        // make sure this works!!
        if (random < (i + 1) * perBoxProbability)
        {
            boxNumber = i;
            break;
        }
    }

    y = std::floor(boxNumber / METEOR_COLUMNS);
    x = boxNumber - y * METEOR_COLUMNS;

    // set the gem to the center positon (using the same calculation from the meteors)
    gem->SetPosition(90.0f * x + 55.0f, 90 * y + 40);
}

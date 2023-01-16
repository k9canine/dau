//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "gem.h"
#include "utils.h"

// sets the position of the gem, where gemX and gemY are the coordinates of the gem in the 2D meteor array
void setGem(CSimpleSprite *gem, int &gemX, int &gemY)
{
    // generate a random spot on the board
    int totalBoxes = METEOR_COLUMNS * METEOR_ROWS;
    int boxNumber = 0;

    srand(time(NULL));
    float random = (float)rand() / RAND_MAX; // random value between 0 and 1
    random = (float)rand() / RAND_MAX;
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

    gemY = std::floor(boxNumber / METEOR_COLUMNS);
    gemX = boxNumber - gemY * METEOR_COLUMNS;

    // set the gem to the center positon (using the same calculation from the meteors)
    gem->SetPosition(90.0f * gemX + 55.0f, 90 * gemY + 40);
}

void checkGetGem(CSimpleSprite *gem, int &gemX, int &gemY, CSimpleSprite *player, float &score, int scoreIncrement)
{
    int modifier = 30;

    float x, y;
    Coordinates upperLeft, upperRight, lowerLeft, lowerRight; // corners of the sprite
    int playerWidth = player->GetWidth() * player->GetScale() - modifier;
    int playerHeight = player->GetHeight() * player->GetScale() - modifier;

    // get position
    player->GetPosition(x, y);

    // get four corners:
    upperLeft.x = x - playerWidth / 2;
    upperLeft.y = y + playerHeight / 2;

    upperRight.x = x + playerWidth / 2;
    upperRight.y = y + playerHeight / 2;

    lowerLeft.x = x - playerWidth / 2;
    lowerLeft.y = y - playerHeight / 2;

    lowerRight.x = x + playerWidth / 2;
    lowerRight.y = y - playerHeight / 2;

    std::vector<Coordinates> corners = {upperLeft, upperRight, lowerLeft, lowerRight};

    // find which box the corners are in
    // check if that spot in the meteor array is nullptr or occupied
    int xIndex, yIndex;

    for (int i = 0; i < corners.size(); i++)
    {
        xIndex = floor(abs(corners[i].x - 15) / 90);
        yIndex = floor(abs(corners[i].y - 10) / 90);

        if (xIndex == gemX && yIndex == gemY)
        {
            setGem(gem, gemX, gemY);
            score += scoreIncrement;
        }
    }
}
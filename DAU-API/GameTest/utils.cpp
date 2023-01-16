//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <vector>
#include <cmath>
#include "App/app.h"
#include "levels.h"
#include "utils.h"

// checks if the current position of the player is in one of the meteor occupied positions
//   sets lose to true if game over condition satsified
void gameOver(CSimpleSprite *player, std::vector<std::vector<CSimpleSprite *>> &allMeteors, bool &lose)
{
    int modifier = 40; // this makes it so that our hitbox is slightly smaller and its easier to move through the obstacles

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

        if (allMeteors[yIndex][xIndex] != nullptr)
        {
            lose = true;
        }
    }
}

// outOfBounds: takes an x and y coordinate and returns if it is a valid position on the screen
bool outOfBounds(float x, float y)
{
    int shipWidth = 40;
    int shipHeight = 30;

    if ((0 + shipWidth <= x && x <= APP_INIT_WINDOW_WIDTH - shipWidth) && (shipHeight <= y && y <= APP_INIT_WINDOW_HEIGHT - shipHeight - 40))
    // subtract an extra 40 pixels from the top for the scoring and level text
    {
        return false;
    }

    return true;
}

void shoot(CSimpleSprite *player, std::vector<std::vector<CSimpleSprite *>> &allMeteors)
{
    float x, y;
    player->GetPosition(x, y);

    int xIndex = floor((x - 15) / 90);
    int yIndex = floor((y - 10) / 90);

    for (int i = yIndex + 1; i < METEOR_ROWS; i++)
    {
        auto meteor = allMeteors[i][xIndex];
        if (meteor != nullptr)
        {
            delete meteor;
            allMeteors[i][xIndex] = nullptr;
            break;
        }
    }
}

// this is not in use because there are some bugs
CSimpleSprite *generateBullet(CSimpleSprite *player)
{
    float x, y;
    player->GetPosition(x, y);

    CSimpleSprite *bullet = App::CreateSprite(".\\TestData\\bullet.bmp", 1, 1);
    bullet->SetPosition(x, y);
    bullet->SetScale(0.1f);

    return bullet;
}
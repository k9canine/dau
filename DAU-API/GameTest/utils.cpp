//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <vector>
#include <cmath>
#include "App/app.h"
#include "levels.h"
#include "utils.h"
// set the meteors and make them appear, then abstract to a new function
// return value: another array to put back into the other array

// generates a row of meteors (an array of pointers to meteor sprites) using the user's level
std::vector<CSimpleSprite *> generateMeteors(float level)
{
    std::vector<int> array = generateArray(level4);
    // std::vector<int> array = {1, 2, 3, 4, 2, 3, 4, 1, 2, 3, 4};
    std::vector<CSimpleSprite *> meteorArray;
    CSimpleSprite *newSprite = nullptr;
    float speed1 = 3.0f / 15.0f;
    float speed2 = 2.0f / 15.0f;
    float speed3 = 2.5f / 15.0f;
    float speed4 = 3.5f / 15.0f;

    for (int i = 0; i < METEOR_COLUMNS; i++)
    {
        switch (array[i])
        {
        case (0):
            meteorArray.emplace_back(nullptr);
            continue;
        case (1):
            // generate a meteor sprite and add that to the array
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed1, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 2});

            meteorArray.emplace_back(newSprite);
            break;
        case (2):
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed2, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 2, 3, 4, 5, 6});

            meteorArray.emplace_back(newSprite);
            break;
        case (3):
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed3, {14, 15, 16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});

            meteorArray.emplace_back(newSprite);
            break;
        case (4):
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed4, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

            meteorArray.emplace_back(newSprite);
            break;
        default:
            break;
        }

        newSprite->SetScale(1.25f);
    }

    return meteorArray;
}

struct Coordinates
{
    int x, y;
};

// checks if the current position of the player is in one of the meteor occupied positions
bool gameOver(CSimpleSprite *player, std::vector<std::vector<CSimpleSprite *>> *allMeteors)
{
    float x, y;
    Coordinates upperLeft, upperRight, lowerLeft, lowerRight; // corners of the sprite
    int playerWidth = player->GetWidth() * player->GetScale();
    int playerHeight = player->GetHeight() * player->GetScale();

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
    int xIndex, yIndex;

    for (int i = 0; i < corners.size(); i++)
    {
        xIndex = floor(abs(corners[i].x - 55) / 90);
        yIndex = floor(abs(corners[i].y - 40) / 90);

        if ((*allMeteors)[yIndex][xIndex] != nullptr)
        {
            return true;
        }
    }

    // check if that spot in the meteor array is nullptr or occupied

    return false;
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
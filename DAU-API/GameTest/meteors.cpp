//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <vector>
#include <cmath>
#include "meteors.h"
#include "App/app.h"
#include "levels.h"
#include "utils.h"

// generates a row of meteors (an array of pointers to meteor sprites) using the user's level
std::vector<CSimpleSprite *> generateMeteors(int level)
{
    std::vector<int> array = generateArray(level);
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
        {
            meteorArray.emplace_back(nullptr);
            continue;
        }

        case (1):
        {
            // generate a meteor sprite and add that to the array
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed1, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 2});

            meteorArray.emplace_back(newSprite);
            break;
        }
        case (2):
        {
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed2, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1, 2, 3, 4, 5, 6});

            meteorArray.emplace_back(newSprite);
            break;
        }
        case (3):
        {
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed3, {14, 15, 16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});

            meteorArray.emplace_back(newSprite);
            break;
        }
        case (4):
        {
            newSprite = App::CreateSprite(".\\TestData\\meteors2.bmp", 16, 2);
            newSprite->SetPosition(90.0f * i + 55.0f, 90 * (METEOR_ROWS - 1) + 40);
            newSprite->CreateAnimation(ANIMATE, speed4, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

            meteorArray.emplace_back(newSprite);
            break;
        }
        default:
        {
            break;
        }
        }

        newSprite->SetScale(1.4f);
    }

    return meteorArray;
}

// this function shifts all of the meteors down and removes the bottom row of meteors, then adds a new row of generated meteors
void updateMeteors(std::vector<std::vector<CSimpleSprite *>> &allMeteors, int level)
{
    // deletes the meteors in the first row before deleting the row
    for (auto meteor : allMeteors.front())
    {
        delete meteor;
    }
    allMeteors.erase(allMeteors.begin());

    // updates the original positions
    for (auto meteorRow : allMeteors)
    {
        for (auto meteor : meteorRow)
        {
            if (meteor)
            {
                float x, y;
                meteor->GetPosition(x, y);
                meteor->SetPosition(x, y - 90);
            }
        }
    }

    // adds to the beginning
    allMeteors.emplace_back(generateMeteors(level)); // option COULD GENERATE EMPTY ROWS IN BETWEEN
}
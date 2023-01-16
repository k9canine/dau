#ifndef UTILS_H
#define UTILS_H

#include "app/app.h"
#include <vector>

extern int METEOR_COLUMNS, METEOR_ROWS;
enum
{
    ANIMATE
};

void gameOver(CSimpleSprite *player, std::vector<std::vector<CSimpleSprite *>> &allMeteors, bool &lose);
bool outOfBounds(float x, float y);
struct Coordinates
{
    int x, y;
};
void shoot(CSimpleSprite *player, std::vector<std::vector<CSimpleSprite *>> &allMeteors);
CSimpleSprite *generateBullet(CSimpleSprite *player);

#endif
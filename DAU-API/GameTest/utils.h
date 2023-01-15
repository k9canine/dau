#ifndef UTILS_H
#define UTILS_H

#include "app/app.h"
#include <vector>

extern int METEOR_COLUMNS, METEOR_ROWS;
enum
{
    ANIMATE
};

std::vector<CSimpleSprite *> generateMeteors(int level);
void gameOver(CSimpleSprite *player, std::vector<std::vector<CSimpleSprite *>> &allMeteors, bool &lose);
bool outOfBounds(float x, float y);
void updateMeteors(std::vector<std::vector<CSimpleSprite *>> &allMeteors, int level);

#endif
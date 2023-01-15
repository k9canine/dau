#ifndef UTILS_H
#define UTILS_H

#include "app/app.h"

extern int METEOR_COLUMNS, METEOR_ROWS;
enum
{
    ANIMATE
};

std::vector<CSimpleSprite *> generateMeteors(float level);
bool gameOver(CSimpleSprite *player, std::vector<std::vector<CSimpleSprite *>> *allMeteors);
bool outOfBounds(float x, float y);

#endif
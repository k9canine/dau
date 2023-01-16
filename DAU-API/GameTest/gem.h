#ifndef GEM_H
#define GEM_H

#include "app/app.h"

void setGem(CSimpleSprite *gem, int &gemX, int &gemY);
void checkGetGem(CSimpleSprite *gem, int &gemX, int &gemY, CSimpleSprite *player, float &score, int scoreIncrement);

#endif
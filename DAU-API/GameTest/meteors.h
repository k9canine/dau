#ifndef METEORS_H
#define METEORS_H

#include "app/app.h"
#include <vector>

std::vector<CSimpleSprite *> generateMeteors(int level);
void updateMeteors(std::vector<std::vector<CSimpleSprite *>> &allMeteors, int level);

#endif
#pragma once

#include "tdefine.h"

bool singleDrop(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void hardDrop(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void lockmino(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
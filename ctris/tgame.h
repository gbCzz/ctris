#pragma once

#include "tdefine.h"

bool singleDrop(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void softDrop(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void lock(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
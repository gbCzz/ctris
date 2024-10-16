#pragma once

#include "tdefine.h"

bool singleDrop(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void hardDrop(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void lockmino(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void leftmove(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);
void rightmove(TETROMINO_t, ROTSTATE_t, int&, int&, int[10][22]);

void rotate(TETROMINO_t, ROTSTATE_t&, ROTSTATE_t, int&, int&, int[10][22]);
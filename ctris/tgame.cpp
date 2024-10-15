#include "tgame.h"
#include "tdefine.h"

bool singleDrop(
	TETROMINO_t fallingmino, 
	ROTSTATE_t rotstate, 
	int& fmCenterX, 
	int& fmCenterY, 
	int field[10][22]
){
	int nextY = fmCenterY;
	bool touched = false;

	// 判断当前位置是否已接触下方方块
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		if (nextY - 1 + elem[Y_POS] < 0 || field[fmCenterX + elem[X_POS]][nextY - 1 + elem[Y_POS]] < 0) {
			touched = true;
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	if (!touched) fmCenterY -= 1; // 如果没有触底就向下掉落一格
	// 更新方块位置，如果触底就锁定
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
	}
	return touched;
}

void hardDrop(
	TETROMINO_t fallingmino,
	ROTSTATE_t rotstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
	int nextY = fmCenterY;
	bool bottomed = false;
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		if (nextY - 1 + elem[Y_POS] < 0 || field[fmCenterX + elem[X_POS]][nextY - 1 + elem[Y_POS]] < 0) {
			bottomed = true;
		}
	}

	while (!bottomed) {
		nextY -= 1;
		for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
			if (nextY - 1 + elem[Y_POS] < 0 || field[fmCenterX + elem[X_POS]][nextY - 1 + elem[Y_POS]] < 0) {
				bottomed = true;
			}
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	fmCenterY = nextY;
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = -fallingmino;
	}
}

void lockmino(
	TETROMINO_t fallingmino,
	ROTSTATE_t rotstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = -fallingmino;
	}
}
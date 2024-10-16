#include "tgame.h"
#include "tdefine.h"

bool singleDrop(
	TETROMINO_t fallingmino,
	ROTSTATE_t rotstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
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
	// 更新方块位置
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
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
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

void leftmove(
	TETROMINO_t fallingmino,
	ROTSTATE_t rotstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
	int nextX = fmCenterX;
	bool touched = false;

	// 判断当前位置是否已接触左方方块
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		if (nextX - 1 + elem[X_POS] < 0 || field[nextX - 1 + elem[X_POS]][fmCenterY + elem[Y_POS]] < 0) {
			touched = true;
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	if (!touched) fmCenterX -= 1; // 如果没有触壁就向左掉落一格
	// 更新方块位置
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
	}
	return;
}

void rightmove(
	TETROMINO_t fallingmino,
	ROTSTATE_t rotstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
	int nextX = fmCenterX;
	bool touched = false;

	// 判断当前位置是否已接触右方方块
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		if (nextX + 1 + elem[X_POS] > 9 || field[nextX + 1 + elem[X_POS]][fmCenterY + elem[Y_POS]] < 0) {
			touched = true;
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	if (!touched) fmCenterX += 1; // 如果没有触壁就向右移动一格
	// 更新方块位置
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
	}
	return;
}

void rotate(TETROMINO_t fallingmino,
	ROTSTATE_t& rotstate,
	ROTSTATE_t targetstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
	for (int i = 0; i < 5; i++) {
		bool rotable = true;
		int wkX = tetrominoInfo[fallingmino].wall_kick[rotstate][i][X_POS] - tetrominoInfo[fallingmino].wall_kick[targetstate][i][X_POS];
		int wkY = tetrominoInfo[fallingmino].wall_kick[rotstate][i][Y_POS] - tetrominoInfo[fallingmino].wall_kick[targetstate][i][Y_POS];

		for (auto elem : tetrominoInfo[fallingmino].shape[targetstate]) {
			if (
				fmCenterX + wkX + elem[X_POS] < 0 ||
				fmCenterX + wkX + elem[X_POS] > 9 ||
				fmCenterY + wkY + elem[Y_POS] < 0 ||
				field[fmCenterX + wkX + elem[X_POS]][fmCenterY + wkY + elem[Y_POS]] < 0
				) {
				rotable = false;
			}
		}

		if (rotable) {
			for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
				field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
			}
			fmCenterX += wkX;
			fmCenterY += wkY;
			rotstate = targetstate;
			for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
				field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
			}
			break;
		}
	}	
}
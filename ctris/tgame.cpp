#include "tgame.h"
#include "tdefine.h"

bool singleDrop(
	TETROMINO_t fallingmino, 
	ROTSTATE_t rotstate, 
	int& fmCenterX, 
	int& fmCenterY, 
	int field[10][22]
){
	int nextY = fmCenterY - 1;
	bool touched = false;

	// 判断下落一格后的位置是否已接触下方方块
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		// nextY - 1 是在判断下落一格后的位置的下方，即再下落一格
		if (field[fmCenterX + elem[X_POS]][nextY - 1 + elem[Y_POS]]) {
			touched = true;
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	fmCenterY += 1;
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
	}
	return touched;
}
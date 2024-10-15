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

	// �ж�����һ����λ���Ƿ��ѽӴ��·�����
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		// nextY - 1 �����ж�����һ����λ�õ��·�����������һ��
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
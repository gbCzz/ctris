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

	// �жϵ�ǰλ���Ƿ��ѽӴ��·�����
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		if (nextY - 1 + elem[Y_POS] < 0 || field[fmCenterX + elem[X_POS]][nextY - 1 + elem[Y_POS]] < 0) {
			touched = true;
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	if (!touched) fmCenterY -= 1; // ���û�д��׾����µ���һ��
	// ���·���λ��
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

bool leftmove(
	TETROMINO_t fallingmino,
	ROTSTATE_t rotstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
	int nextX = fmCenterX;
	bool touched = false;

	// �жϵ�ǰλ���Ƿ��ѽӴ��󷽷���
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		if (nextX - 1 + elem[X_POS] < 0 || field[nextX - 1 + elem[X_POS]][fmCenterY + elem[Y_POS]] < 0) {
			touched = true;
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	if (!touched) fmCenterX -= 1; // ���û�д��ھ��������һ��
	// ���·���λ��
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
	}
	return touched;
}

bool rightmove(
	TETROMINO_t fallingmino,
	ROTSTATE_t rotstate,
	int& fmCenterX,
	int& fmCenterY,
	int field[10][22]
) {
	int nextX = fmCenterX;
	bool touched = false;

	// �жϵ�ǰλ���Ƿ��ѽӴ��ҷ�����
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		if (nextX + 1 + elem[X_POS] > 9 || field[nextX + 1 + elem[X_POS]][fmCenterY + elem[Y_POS]] < 0) {
			touched = true;
		}
	}

	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = 0;
	}

	if (!touched) fmCenterX += 1; // ���û�д��ھ������ƶ�һ��
	// ���·���λ��
	for (auto elem : tetrominoInfo[fallingmino].shape[rotstate]) {
		field[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
	}
	return touched;
}
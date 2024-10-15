#include <graphics.h>
#include <queue>
#include <time.h>
#include <stdlib.h>

#include "tdraw.h"
#include "tdefine.h"
#include "tgame.h"

std::deque<TETROMINO_t> spawnQueue;

int main() {
	initgraph(MAX_WIDTH, MAX_HEIGHT);
	BeginBatchDraw();

	bool kbexit = false;
	clock_t kblmove = 0;
	clock_t kbrmove = 0;

	int sdf = 201;
	int arr = 0;
	int das = 177;

	bool softdropping = false;
	bool hdropped = false;

	ExMessage m;

	bool gaming = true;
	TETROMINO_t fallingmino = 0;
	ROTSTATE_t fmRotState = 0;
	int fmCenterX = -1, fmCenterY = -1;
	clock_t lastfall = 0;
	bool lastfalltouched = false;
	clock_t lastlmove = 0;
	clock_t lastrmove = 0;

	TETROMINO_t tetrominofield[10][22] = {};

	while (!kbexit) {
		// 获取控制
		while (peekmessage(&m, EX_KEY)) {
			if (m.message == WM_KEYDOWN) {
				switch (m.vkcode) {
					case VK_ESCAPE:	kbexit = true; break;
					case VK_LEFT: 
						if(!kblmove) kblmove = clock();
						leftmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						lastlmove = clock();
						break;
					case VK_RIGHT: 
						if(!kbrmove) kbrmove = clock();
						rightmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						lastrmove = clock();
						break;
					case VK_UP:
					case 'X': break;
					case 'Z': break;
					case 'A': break;
					case 'C':
					case VK_SHIFT: break;
					case VK_SPACE:
						hdropped = true;
						hardDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						lockmino(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						break;
					case VK_DOWN: softdropping = true; break;
				}
			}
			if (m.message == WM_KEYUP) {
				switch (m.vkcode) {
					case VK_ESCAPE:	kbexit = false; break;
					case VK_LEFT: kblmove = 0; break;
					case VK_RIGHT: kbrmove = 0; break;
					case VK_UP:
					case 'X': break;
					case 'Z': break;
					case 'A': break;
					case 'C':
					case VK_SHIFT: break;
					case VK_SPACE: break;
					case VK_DOWN: softdropping = false; break;
				}
			}
		}

		// 检查生成队列中剩余方块个数，如不足，则用洗牌算法生成新的一包
		if (spawnQueue.size() <= 6) {
			TETROMINO_t bag[] = { 1, 2, 3, 4, 5, 6, 7 };
			for (int i = 0; i < 7; i++) {
				srand(clock());
				int ind = rand() % (7 - i);
				TETROMINO_t tmp = bag[ind];
				bag[ind] = bag[6 - i];
				bag[6 - i] = tmp;
			}
			for (int i = 0; i < 7; i++) {
				spawnQueue.push_back(bag[i]);
			}
		}

		// 检查是否有正在掉落的方块，如没有，则生成一个
		if (gaming && !fallingmino) {
			fallingmino = spawnQueue.front();
			fmCenterX = 4;
			fmCenterY = 20;
			for (auto elem : tetrominoInfo[fallingmino].shape[RST_0]) {
				tetrominofield[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
			}
			spawnQueue.pop_front();
			lastfall = clock();
		}

		if (!hdropped) {
			if (!softdropping && clock() - lastfall >= 1000 && !lastfalltouched) {
				lastfalltouched = singleDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastfall = clock();
			} else if (sdf <= 200 && softdropping && clock() - lastfall >= 1000 / sdf && !lastfalltouched) {
				lastfalltouched = singleDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastfall = clock();
			} else if (sdf > 200 && softdropping && !lastfalltouched) {
				hardDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastfalltouched = true;
				lastfall = clock();
			}
			if (kblmove && clock() - kblmove >= das && clock() - lastlmove >= arr) {
				leftmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastlmove = clock();
			}
			if (!kblmove && kbrmove && clock() - kbrmove >= das && clock() - lastrmove >= arr) {
				rightmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastrmove = clock();
			}
			if (kblmove || kbrmove) lastfalltouched = false;
			if (clock() - lastfall >= 500 && lastfalltouched) {
				lockmino(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				fallingmino = 0;
				lastfalltouched = false;
			}
		} else {
			fallingmino = 0;
			hdropped = false;
			lastfall = clock();
		};

		// 绘制
		cleardevice();

		// 绘制地图
		drawPlayingField();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 22; j++) {
				if (tetrominofield[i][j] == 0) continue;
				TETROMINO_t drawingmino = tetrominofield[i][j] > 0 ? tetrominofield[i][j] : -tetrominofield[i][j];
				drawMino(i, j, tetrominoInfo[drawingmino].bcolor, tetrominoInfo[drawingmino].dcolor);
			}
		}
		// 刷新屏幕
		FlushBatchDraw();
	}

	EndBatchDraw();
	closegraph();
	return 0;
}
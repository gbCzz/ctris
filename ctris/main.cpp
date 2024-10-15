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
	bool kblmove = false;
	bool kbrmove = false;
	bool kblrot = false;
	bool kbrrot = false;
	bool kb2rot = false;
	bool kbhold = false;
	bool kbsdrop = false;
	bool kbhdrop = false;
	ExMessage m;

	bool gaming = true;
	TETROMINO_t fallingmino = 0;
	ROTSTATE_t fmRotState = 0;
	int fmCenterX = -1, fmCenterY = -1;
	clock_t lastfall = 0;
	bool lastfalltouched = false;

	TETROMINO_t tetrominofield[10][22] = {};

	while (!kbexit) {
		// 获取控制
		while (peekmessage(&m, EX_KEY)) {
			if (m.message == WM_KEYDOWN) {
				switch (m.vkcode) {
					case VK_ESCAPE:	kbexit = true; break;
					case VK_LEFT: kblmove = true; break;
					case VK_RIGHT: kbrmove = true; break;
					case VK_UP:
					case 'X': kbrrot = true; break;
					case 'Z': kblrot = true; break;
					case 'A': kb2rot = true; break;
					case 'C':
					case VK_SHIFT: kbhold = true; break;
					case VK_SPACE: kbhdrop = true; break;
					case VK_DOWN: kbsdrop = true; break;
				}
			}
			if (m.message == WM_KEYUP) {
				switch (m.vkcode) {
					case VK_ESCAPE:	kbexit = false; break;
					case VK_LEFT: kblmove = false; break;
					case VK_RIGHT: kbrmove = false; break;
					case VK_UP:
					case 'x': kbrrot = false; break;
					case 'z': kblrot = false; break;
					case 'a': kb2rot = false; break;
					case 'c':
					case VK_SHIFT: kbhold = false; break;
					case VK_SPACE: kbhdrop = false; break;
					case VK_DOWN: kbsdrop = false; break;
				}
			}
		}

		// 检查生成队列中剩余方块个数，如不足，则用洗牌算法生成新的一包
		if (spawnQueue.size() <= 6) {
			TETROMINO_t bag[] = { 1, 2, 3, 4, 5, 6, 7 };
			for (int i = 0; i < 7; i++) {
				srand(time(NULL));
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
			lastfall = clock();
		}

		if (clock() - lastfall >= 1000 && !lastfalltouched) {
			lastfalltouched = singleDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
			lastfall = clock();
		}

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
		Sleep(1);
	}

	EndBatchDraw();
	closegraph();
	return 0;
}
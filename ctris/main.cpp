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
	bool rotated = false;
	bool holded = false;

	ExMessage m;

	bool gaming = true;
	TETROMINO_t fallingmino = 0;
	TETROMINO_t holdingmino = 0;
	ROTSTATE_t fmRotState = 0;
	int fmCenterX = -1, fmCenterY = -1;
	clock_t lastfall = 0;
	bool lastfalltouched = false;
	clock_t lastlmove = 0;
	clock_t lastrmove = 0;
	clock_t lastrot = 0;

	TETROMINO_t tetrominofield[10][22] = {};

	while (!kbexit) {
		// ��ȡ����
		while (peekmessage(&m, EX_KEY)) {
			if (m.message == WM_KEYDOWN) {
				switch (m.vkcode) {
					case VK_ESCAPE:	kbexit = true; break;
					case VK_LEFT:
						if (!kblmove) kblmove = clock();
						leftmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						lastlmove = clock();
						break;
					case VK_RIGHT:
						if (!kbrmove) kbrmove = clock();
						rightmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						lastrmove = clock();
						break;
					case VK_UP:
					case 'X':
						if (!rotated) {
							rotated = true;
							rotate(fallingmino, fmRotState, (fmRotState + 1) % 4, fmCenterX, fmCenterY, tetrominofield);
							lastrot = clock();
						}
						break;
					case 'Z':
						if (!rotated) {
							rotated = true;
							rotate(fallingmino, fmRotState, (fmRotState + 3) % 4, fmCenterX, fmCenterY, tetrominofield);
							lastrot = clock();
						}
						break;
					case 'A':
						if (!rotated) {
							rotated = true;
							rotate(fallingmino, fmRotState, (fmRotState + 2) % 4, fmCenterX, fmCenterY, tetrominofield);
							lastrot = clock();
						}
						break;
					case 'C':
					case VK_SHIFT:
						if (!holded) {
							holded = true;
							holdexchange(fallingmino, holdingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						}
						break;
					case VK_SPACE:
						hdropped = true;
						holded = false;
						hardDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						lockmino(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
						flushfullline(tetrominofield);
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
					case 'X':
						rotated = false;
						break;
					case 'Z':
						rotated = false;
						break;
					case 'A':
						rotated = false;
						break;
					case 'C':
					case VK_SHIFT: break;
					case VK_SPACE: break;
					case VK_DOWN: softdropping = false; break;
				}
			}
		}

		// ������ɶ�����ʣ�෽��������粻�㣬����ϴ���㷨�����µ�һ��
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

		// ����Ƿ������ڵ���ķ��飬��û�У�������һ��
		if (gaming && !fallingmino) {
			fallingmino = spawnQueue.front();
			fmRotState = 0;
			fmCenterX = 4;
			fmCenterY = 20;
			for (auto elem : tetrominoInfo[fallingmino].shape[RST_0]) {
				tetrominofield[fmCenterX + elem[X_POS]][fmCenterY + elem[Y_POS]] = fallingmino;
			}
			spawnQueue.pop_front();
			lastfall = clock();
		}

		if (!hdropped) {
			// û�������������ϴ������Ѿ� 1000ms�����ϴ������û�д���
			if (!softdropping && clock() - lastfall >= 1000 && !lastfalltouched) {
				lastfalltouched = singleDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastfall = clock();
			} // ������SDF ���ޣ��������ĳ� 1000/SDF ms
			else if (sdf <= 200 && softdropping && clock() - lastfall >= 1000 / sdf && !lastfalltouched) {
				lastfalltouched = singleDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastfall = clock();
			} // ������SDF ����󣬰���Ӳ���������½�������
			else if (sdf > 200 && softdropping && !lastfalltouched) {
				hardDrop(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastfalltouched = true;
				lastfall = clock();
			}

			// ��ס����Ѿ������� DAS ms��ƽ�Ƽ��Ϊ ARR
			if (kblmove && clock() - kblmove >= das && clock() - lastlmove >= arr) {
				leftmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastlmove = clock();
			}
			// �Ҽ�ͬ���������ȼ��������
			if (!kblmove && kbrmove && clock() - kbrmove >= das && clock() - lastrmove >= arr) {
				rightmove(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				lastrmove = clock();
			}
			// �ƶ�����ת�����飬����һ��ѭ�������ж��Ƿ������䣬��ֹ����ƽ����תȴ��ǰ����
			if (kblmove || kbrmove || rotated) {
				lastfalltouched = false;
			};

			// ����ʱ������ϴβ��� 500 ms
			if (clock() - max(lastfall, max(lastrot, max(lastrmove, lastlmove))) >= 500 && lastfalltouched) {
				lockmino(fallingmino, fmRotState, fmCenterX, fmCenterY, tetrominofield);
				flushfullline(tetrominofield);
				holded = false;
				fallingmino = 0;
				lastfalltouched = false;
			}
		} else {
			lastfalltouched = 0;
			fallingmino = 0;
			hdropped = false;
			lastfall = clock();
		};

		// ����
		cleardevice();

		// ���Ƶ�ͼ
		drawPlayingField();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 22; j++) {
				if (tetrominofield[i][j] == 0) continue;
				TETROMINO_t drawingmino = tetrominofield[i][j] > 0 ? tetrominofield[i][j] : -tetrominofield[i][j];
				drawMino(i, j, tetrominoInfo[drawingmino].bcolor, tetrominoInfo[drawingmino].dcolor);
			}
		}

		// ������Ӱ
		int nextY = fmCenterY;
		bool bottomed = false;
		for (auto elem : tetrominoInfo[fallingmino].shape[fmRotState]) {
			if (nextY - 1 + elem[Y_POS] < 0 || tetrominofield[fmCenterX + elem[X_POS]][nextY - 1 + elem[Y_POS]] < 0) {
				bottomed = true;
			}
		}

		while (!bottomed) {
			nextY -= 1;
			for (auto elem : tetrominoInfo[fallingmino].shape[fmRotState]) {
				if (nextY - 1 + elem[Y_POS] < 0 || tetrominofield[fmCenterX + elem[X_POS]][nextY - 1 + elem[Y_POS]] < 0) {
					bottomed = true;
				}
			}
		}

		for (auto elem : tetrominoInfo[fallingmino].shape[fmRotState]) {
			drawMino(fmCenterX + elem[X_POS], nextY + elem[Y_POS], tetrominoInfo[fallingmino].dcolor, 0);
		}

		// ���� hold ����
		RECT tHOLDarea = {
			MAX_WIDTH / 2 - 5 * CELL_LENGTH + (-5) * CELL_LENGTH + 1,
			MAX_HEIGHT / 2 + 11 * CELL_LENGTH - (20) * CELL_LENGTH,
			MAX_WIDTH / 2 - 5 * CELL_LENGTH + (-1) * CELL_LENGTH + 1,
			MAX_HEIGHT / 2 + 11 * CELL_LENGTH - (18) * CELL_LENGTH,
		};
		settextstyle(CELL_LENGTH * 3 / 2, 0, _T("Arial"));
		drawtext(_T("HOLD"), &tHOLDarea, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		for (auto elem : tetrominoInfo[holdingmino].shape[RST_0]) {
			if (!holded)
				drawMino(-4 + elem[X_POS], 16 + elem[Y_POS], tetrominoInfo[holdingmino].bcolor, tetrominoInfo[holdingmino].dcolor);
			else
				drawMino(-4 + elem[X_POS], 16 + elem[Y_POS], tetrominoInfo[holdingmino].dcolor, 0);
		}

		// ˢ����Ļ
		FlushBatchDraw();
	}

	EndBatchDraw();
	closegraph();
	return 0;
}
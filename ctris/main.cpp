#include <graphics.h>
#include <queue>
#include <time.h>
#include <stdlib.h>

#include "tdraw.h"
#include "tdefine.h"

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
	time_t lastfall = 0;

	TETROMINO_t tetrominofield[22][10] = {};

	while (!kbexit) {
		// ��ȡ����
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
		// ������ɶ�����ʣ�෽��������粻�㣬����ϴ���㷨�����µ�һ��
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
		// ����
		cleardevice();

		// ���ƿյ�ͼ
		drawPlayingField();
		// ˢ����Ļ
		FlushBatchDraw();
		Sleep(1);
	}

	EndBatchDraw();
	closegraph();
	return 0;
}

void drawPlayingField() {
	// ��ɫ�����ߣ�+-1 ��Ϊ�˱�ʵ�ʵ�ͼ��һȦ��ǡ�ÿ�ס
	setlinecolor(WHITE);
	line(
		MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1,
		MAX_WIDTH / 2 + 5 * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1
	);
	line(
		MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1,
		MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 - 9 * CELL_LENGTH - 1
	);
	line(
		MAX_WIDTH / 2 + 5 * CELL_LENGTH + 1, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1,
		MAX_WIDTH / 2 + 5 * CELL_LENGTH + 1, MAX_HEIGHT / 2 - 9 * CELL_LENGTH - 1
	);

	// ���ɫ������
	setlinecolor(DARKGRAY);
	for (int i = 0; i < 5; i++) {
		line(
			MAX_WIDTH / 2 - i * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH,
			MAX_WIDTH / 2 - i * CELL_LENGTH, MAX_HEIGHT / 2 - 9 * CELL_LENGTH
		);
		line(
			MAX_WIDTH / 2 + i * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH,
			MAX_WIDTH / 2 + i * CELL_LENGTH, MAX_HEIGHT / 2 - 9 * CELL_LENGTH
		);
	}
	for (int i = 0; i < 10; i++) {
		line(
			MAX_WIDTH / 2 - 5 * CELL_LENGTH + 1, MAX_HEIGHT / 2 + i * CELL_LENGTH + 1 + CELL_LENGTH,
			MAX_WIDTH / 2 + 5 * CELL_LENGTH, MAX_HEIGHT / 2 + i * CELL_LENGTH + 1 + CELL_LENGTH
		);
		line(
			MAX_WIDTH / 2 - 5 * CELL_LENGTH + 1, MAX_HEIGHT / 2 - i * CELL_LENGTH + 1 + CELL_LENGTH,
			MAX_WIDTH / 2 + 5 * CELL_LENGTH, MAX_HEIGHT / 2 - i * CELL_LENGTH + 1 + CELL_LENGTH
		);
	}
	return;
}

/// <summary>
/// ��ָ���ĵ�ͼ�����л��Ʒ���
/// </summary>
/// <param name="xF">ָ�������ڵ�ͼ�еĵ�ͼ���� x ����</param>
/// <param name="yF">ָ�������ڵ�ͼ�еĵ�ͼ���� y ����</param>
/// <param name="bcolor">����ָ�����ӵ���ɫ��ɫ</param>
/// <param name="dcolor">����ָ�����ӵİ�ɫ��ɫ</param>
void drawMino(int xF, int yF, COLORREF bcolor, COLORREF dcolor) {
	int x1 = MAX_WIDTH / 2 - 5 * CELL_LENGTH + xF * CELL_LENGTH + 1;
	int y1 = MAX_HEIGHT / 2 + 11 * CELL_LENGTH - yF * CELL_LENGTH;
	int x2 = x1 + CELL_LENGTH - 1;
	int y2 = y1 - CELL_LENGTH + 1;

	// ��ɫ������������
	setfillcolor(bcolor);
	solidrectangle(x1, y1, x2, y2);

	// ���½ǻ��ư�ɫ������Ϊ��Ӱ�ĵ�ɫ
	setfillcolor(dcolor);
	POINT dtrpt[] = { x1, y1, x2, y2, x2, y1 };
	solidpolygon(dtrpt, 3);

	// �м������ɫС��������ס���ְ�ɫ��ͬʱ�ð�ɫ�߿�������
	setfillcolor(bcolor);
	setlinecolor(dcolor);
	// ��������㲻����ʲôʱ�� +1 ʲôʱ�� -1 �ˣ���������˳�۾�����
	fillrectangle(
		(x1 + x2) / 2 - CELL_LENGTH / 4 + 2, (y1 + y2) / 2 + CELL_LENGTH / 4,
		(x1 + x2) / 2 + CELL_LENGTH / 4, (y1 + y2) / 2 - CELL_LENGTH / 4 + 2
	);
	return;
}
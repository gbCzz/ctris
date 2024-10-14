#include <graphics.h>

#include "tdraw.h"
#include "tdefine.h"

#define MAX_WIDTH 960
#define MAX_HEIGHT 720
#define CELL_LENGTH 32

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

		// 绘制
		cleardevice();

		// 绘制空地图
		drawPlayingField();
		// 刷新屏幕
		FlushBatchDraw();
		Sleep(10);
	}

	EndBatchDraw();
	closegraph();
	return 0;
}

void drawPlayingField() {
	// 白色外侧框线，+-1 是为了比实际地图大一圈，恰好框住
	setlinecolor(WHITE);
	line(
		MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1,
		MAX_WIDTH / 2 + 5 * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1
	);
	line(
		MAX_WIDTH / 2 - 5 * CELL_LENGTH - 1, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1,
		MAX_WIDTH / 2 - 5 * CELL_LENGTH - 1, MAX_HEIGHT / 2 - 9 * CELL_LENGTH - 1
	);
	line(
		MAX_WIDTH / 2 + 5 * CELL_LENGTH + 1, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1,
		MAX_WIDTH / 2 + 5 * CELL_LENGTH + 1, MAX_HEIGHT / 2 - 9 * CELL_LENGTH - 1
	);

	// 深灰色网格线
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
			MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 + i * CELL_LENGTH + 1 + CELL_LENGTH,
			MAX_WIDTH / 2 + 5 * CELL_LENGTH, MAX_HEIGHT / 2 + i * CELL_LENGTH + 1 + CELL_LENGTH
		);
		line(
			MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 - i * CELL_LENGTH + 1 + CELL_LENGTH,
			MAX_WIDTH / 2 + 5 * CELL_LENGTH, MAX_HEIGHT / 2 - i * CELL_LENGTH + 1 + CELL_LENGTH
		);
	}
	return;
}

void drawMino(int xF, int yF, COLORREF color) {
	return;
}
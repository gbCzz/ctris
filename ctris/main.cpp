#include <graphics.h>

#include "tdraw.h"
#include "tdefine.h"

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
		drawMino(9, 0, RED, D_RED);
		drawMino(0, 0, RED, D_RED);
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
		MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 + 11 * CELL_LENGTH + 1,
		MAX_WIDTH / 2 - 5 * CELL_LENGTH, MAX_HEIGHT / 2 - 9 * CELL_LENGTH - 1
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
/// 在指定的地图格子中绘制方块
/// </summary>
/// <param name="xF">指定格子在地图中的地图坐标 x 坐标</param>
/// <param name="yF">指定格子在地图中的地图坐标 y 坐标</param>
/// <param name="bcolor">绘制指定格子的亮色颜色</param>
/// <param name="dcolor">绘制指定格子的暗色颜色</param>
void drawMino(int xF, int yF, COLORREF bcolor, COLORREF dcolor) {
	int x1 = MAX_WIDTH / 2 - 5 * CELL_LENGTH + xF * CELL_LENGTH + 1;
	int y1 = MAX_HEIGHT / 2 + 11 * CELL_LENGTH - yF * CELL_LENGTH;
	int x2 = x1 + CELL_LENGTH - 1;
	int y2 = y1 - CELL_LENGTH + 1;
	setfillcolor(bcolor);
	solidrectangle(x1, y1, x2, y2);
	setfillcolor(dcolor);
	POINT dtrpt[] = {x1, y1, x2, y2, x2, y1};
	solidpolygon(dtrpt, 3);
	setfillcolor(bcolor);
	setlinecolor(dcolor);
	fillrectangle(
		(x1 + x2) / 2 - CELL_LENGTH / 4 + 1, (y1 + y2) / 2 + CELL_LENGTH / 4,
		(x1 + x2) / 2 + CELL_LENGTH / 4, (y1 + y2) / 2 - CELL_LENGTH / 4 + 1
	);
	return;
}
#include <graphics.h>

#define MAX_WIDTH 960
#define MAX_HEIGHT 720
#define CELL_LENGTH 32

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
}

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
	ExMessage m;

	while (!kbexit) {
		// 获取控制
		while (peekmessage(&m, EX_KEY)) {
			if (m.message == WM_KEYDOWN) {
				switch (m.vkcode) {
					case VK_ESCAPE:	
						kbexit = true;
						break;
					case VK_LEFT: 
						kblmove = true;
						break;
					case VK_RIGHT:
						kbrmove = true;
						break;
					case VK_UP:
					case 'x':
						kbrrot = true;
						break;
					case 'z':
						kblrot = true;
						break;
					case 'a':
						kb2rot = true;
						break;
					case 'c':
					case VK_SHIFT:
						kbhold = true;
						break;
				}
			}
		}

		// 绘制
		cleardevice();

		// 绘制空地图
		drawPlayingField();
		// 刷新屏幕
		FlushBatchDraw();

	}

	EndBatchDraw();
	closegraph();
	return 0;
}

#include <easyx.h>

#include "tdraw.h"
#include "tdefine.h"

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

	// 亮色绘制完整方块
	setfillcolor(bcolor);
	solidrectangle(x1, y1, x2, y2);

	// 右下角绘制暗色三角作为阴影的底色
	setfillcolor(dcolor);
	POINT dtrpt[] = { x1, y1, x2, y2, x2, y1 };
	solidpolygon(dtrpt, 3);

	// 中间绘制亮色小正方形遮住部分暗色，同时用暗色边框表现棱边
	setfillcolor(bcolor);
	setlinecolor(dcolor);
	// 你妈逼我算不明白什么时候 +1 什么时候 -1 了，反正看着顺眼就完事
	fillrectangle(
		(x1 + x2) / 2 - CELL_LENGTH / 4 + 2, (y1 + y2) / 2 + CELL_LENGTH / 4,
		(x1 + x2) / 2 + CELL_LENGTH / 4, (y1 + y2) / 2 - CELL_LENGTH / 4 + 2
	);
	return;
}
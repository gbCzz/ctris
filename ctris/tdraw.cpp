#include <easyx.h>

#include "tdraw.h"
#include "tdefine.h"

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
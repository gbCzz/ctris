#include <graphics.h>

#define MAX_WIDTH 1280
#define MAX_HEIGHT 720

int main()
{
	initgraph(MAX_WIDTH, MAX_HEIGHT);
	BeginBatchDraw();

	bool exit = false;

	ExMessage m;

	while (!exit)
	{
		// 获取控制
		while (peekmessage(&m, EX_KEY))
		{
			if (m.message == WM_KEYDOWN)
			{
				switch (m.vkcode)
				{
				case VK_ESCAPE:	exit = true;	break;
				}
			}
		}

		// 绘制
		cleardevice();


		// 刷新屏幕
		FlushBatchDraw();

	}

	EndBatchDraw();
	closegraph();
	return 0;
}

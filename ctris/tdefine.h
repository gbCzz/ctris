#pragma once

#define MAX_WIDTH 960
#define MAX_HEIGHT 720
#define CELL_LENGTH 32

#define TID_I 0
#define TID_J 1
#define TID_L 2
#define TID_O 3
#define TID_S 4
#define TID_T 5
#define TID_Z 6

#define RST_0 0
#define RST_R 1
#define RST_2 2
#define RST_L 3

#define X_POS 0
#define Y_POS 1

#define ORANGE 0x00AAFF

#define D_CYAN 0x666600
#define D_BLUE 0x660000
#define D_ORANGE 0x0066AA
#define D_YELLOW 0x00AAAA
#define D_GREEN 0x006600
#define D_MAGENTA 0x660066
#define D_RED 0x000066

static const struct Tetromino {
	int shape[4][2];
	int wall_kick[4][5][2];
	COLORREF color;
} tetrominoInfo[7] = {
	{
		{{0, 0}, {-1, 0}, {1, 0}, {2, 0}},
		{
			{{0, 0}, {-1, 0}, {+2, 0}, {-1, 0}, {+2, 0}},
			{{-1, 0}, {0, 0}, {0, 0}, {0, +1}, {0, -2}},
			{{-1, +1}, {+1, +1}, {-2, +1}, {+1, 0}, {-2, 0}},
			{{0, +1}, {0, +1}, {0, +1}, {0, -1}, {0, +2}},
		},
		CYAN
	}, // I tetromino info
	{
		{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}},
		{
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}},
		},
		BLUE
	}, // J tetromino info
	{
		{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}},
		{
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}},
		},
		ORANGE
	}, // L tetromino info
	{
		{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}},
		{
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, -1}, {0, -1}, {0, -1}, {0, -1}, {0, -1}},
			{{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}},
			{{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}},
		},
		YELLOW
	}, // O tetromino info
	{
		{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}},
		{
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}},
		},
		GREEN
	}, // S tetromino info
	{
		{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}},
		{
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}},
		},
		MAGENTA
	}, // T tetromino info
	{
		{{0, 0}, {-1, 0}, {-1, 1}, {1, 0}},
		{
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {+1, 0}, {+1, -1}, {0, +2}, {+1, +2}},
			{{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
			{{0, 0}, {-1, 0}, {-1, -1}, {0, +2}, {-1, +2}},
		},
		RED
	}, // z tetromino info
};
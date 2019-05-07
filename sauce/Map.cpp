#include <DxLib.h>
#include "Map.h"

Map::Map()
{
	Init();
}

Map::~Map()
{
}

void Map::Init()
{
	frame = LoadGraph("image/SFrame.png");
	minLadder = LoadGraph("image/Donkey Kong_ladder2.png");
	exLongLadder = LoadGraph("image/Donkey Kong_ladder4.png");
	ladder = LoadGraph("image/ladder.png");
	barrel = LoadGraph("image/Donkey Kong_4Barrel.png");
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			fPos[i][j].x = -31;
			fPos[i][j].y = 0;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			lPos[i][j].x = 0;
			lPos[i][j].y = 0;
		}
	}
}

void Map::Draw()
{

	//-----------梯子
	// 1段目
	DrawGraph(31 * 3 + 20, 337, minLadder, true);
	DrawGraph(31 * 3 + 20, 309, minLadder, true);

	// 2段目(右)
	lPos[1][1].x = 31 * 4 + 20;
	for (int i = 0; i < 5; i++)
	{
		lPos[1][1].y = 252 + (8 * i);
		DrawGraph(lPos[1][1].x, lPos[1][1].y, ladder, true);
	}

	// 3段目(左)
	lPos[1][2].x = 31 * 6;
	for (int i = 0; i < 5; i++)
	{
		lPos[1][2].y = 203 + (8 * i);
		DrawGraph(lPos[1][2].x, lPos[1][2].y, ladder, true);
	}
	DrawGraph(31 * 3, 212, minLadder, true);
	DrawGraph(31 * 3, 243, minLadder, true);


	// 4段目(右)
	lPos[1][3].x = 31 * 4;
	for (int i = 0; i < 5; i++)
	{
		lPos[1][3].y = 157 + (8 * i);
		DrawGraph(lPos[1][3].x, lPos[1][3].y, ladder, true);
	}
	DrawGraph(31 * 7 + 20, 165, minLadder, true);
	DrawGraph(31 * 7 + 20, 194, minLadder, true);

	// 5段目
	DrawGraph(31 * 4 + 15, 120, minLadder, true);
	DrawGraph(31 * 4 + 15, 145, minLadder, true);

	// 6段目
	lPos[0][5].x = 31 * 6 - 1;
	for (int i = 0; i < 7; i++)
	{
		lPos[0][5].y = 53 + (8 * i);
		DrawGraph(lPos[0][5].x, lPos[0][5].y, ladder, true);
	}
	for (int i = 0; i < 4; i++)
	{
		DrawGraph(31 * 4 - 1, 78 - (i * 32), exLongLadder, true);
	}
	for (int i = 0; i < 4; i++)
	{
		DrawGraph(31 * 3 + 10, 78 - (i * 32), exLongLadder, true);
	}

	// 中心の3つ(2右,3左,4右)の梯子を強引に補完
	DrawGraph(lPos[1][1].x, lPos[1][1].y + 9, minLadder, true);
	DrawGraph(lPos[1][2].x, lPos[1][2].y + 9, minLadder, true);
	DrawGraph(lPos[1][3].x, lPos[1][3].y + 9, minLadder, true);


	// 右の3つ
	for (int i = 0; i < 3; i++)
	{
		lPos[0][i * 2].x = 31 * 8 + 11;
		for (int j = 0; j < 5; j++)
		{
			lPos[0][i * 2].y = (304 - (i * 96)) + (8 * j);
			DrawGraph(lPos[0][i * 2].x, lPos[0][i * 2].y, ladder, true);
		}
	}
	// 左の2つ
	lPos[0][1].x = 31 * 2;
	for (int j = 0; j < 5; j++)
	{
		lPos[0][1].y = (255
			+ (8 * j));
		DrawGraph(lPos[0][1].x, lPos[0][1].y, ladder, true);
	}
	lPos[0][3].x = 31 * 2;
	for (int j = 0; j < 5; j++)
	{
		lPos[0][3].y = (229 - 70) + (8 * j);
		DrawGraph(lPos[0][3].x, lPos[0][3].y, ladder, true);
	}

	//----------足場
	// 1段目
	for (int i = 0; i < 10; i++)
	{
		fPos[i][0].x = 31 * i;
		if (i < 5)
		{	
			fPos[i][0].y = 348;
			DrawGraph(fPos[i][0].x, fPos[i][0].y, frame, true);
		}
		if (i >= 5 && i < 10)
		{
			fPos[i][0].y = 348 - count;
			DrawGraph(fPos[i][0].x, fPos[i][0].y, frame, true);
			count++;
		}
	}

	// 2段目
	for (int i = 0; i < 9; i++)
	{
		fPos[i][1].x = 31 * i + 10;
		fPos[i][1].y = 300 - count;
		DrawGraph(fPos[i][1].x, fPos[i][1].y, frame, true);
		count--;
	}

	// 3段目
	for (int i = 0; i < 9; i++)
	{
		fPos[i][2].x = 31 * i + 31;
		fPos[i][2].y = 252 - count;
		DrawGraph(fPos[i][2].x, fPos[i][2].y, frame, true);
		count++;
	}

	// 4段目
	for (int i = 0; i < 9; i++)
	{
		fPos[i][3].x = 31 * i + 11;
		fPos[i][3].y = 204 - count;
		DrawGraph(fPos[i][3].x, fPos[i][3].y, frame, true);
		count--;
	}

	// 5段目
	for (int i = 0; i < 9; i++)
	{
		fPos[i][4].x = 31 * (i + 1);
		fPos[i][4].y = 156 - count;
		DrawGraph(fPos[i][4].x, fPos[i][4].y, frame, true);
		count++;
	}

	// 6段目
	for (int i = 0; i < 9; i++)
	{
		fPos[i][5].x = 31 * i + 11;
		if (i < 5)
		{
			fPos[i][5].y = 108;
			DrawGraph(fPos[i][5].x, fPos[i][5].y, frame, true);
			count = 1;
		}
		if (i >= 5 && i < 9)
		{
			fPos[i][5].y = 108 + count;
 			DrawGraph(fPos[i][5].x, fPos[i][5].y, frame, true);
			count++;		
		}
	}
	count = 1;

	// ピーチ台
	for (int i = 1; i < 4; i++)
	{
		fPos[i][6].x = 31 * (2 + i) + 10;
		if (i == 1)
		{
			fPos[i][6].y = 65;
			DrawGraph(fPos[i][6].x, fPos[i][6].y, frame, true);
		}
		else if (i > 1)
		{
			fPos[i][6].y = 65 - 12;
			DrawGraph(fPos[i][6].x, fPos[i][6].y, frame, true);
		}
	}

	// 4つの樽
	DrawGraph(2, 57, barrel, true);

	//DrawFormatString(10, 10, 0xffffff, "x:%f y:%f", fPos[5][0].x,fPos[5][0].y);
}

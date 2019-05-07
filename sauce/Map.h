#pragma once

#include <DxLib.h>

class Map {
private:
	typedef struct {
		float x;
		float y;
	}Vec2;

	int frame;
	int minLadder;
	int exLongLadder;
	int ladder;
	int barrel;
	int count = 0;
public:
	Map();
	~Map();

	Vec2 fPos[10][7];	//fPos[X][Y]
	Vec2 lPos[2][6];

	void Init();
	void Draw();
};


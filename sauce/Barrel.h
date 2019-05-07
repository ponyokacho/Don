#pragma once

class Map;
class HitCheck;
class Donkey;
class Player;

class Barrel {
private:
	struct Vec2{
		float x;
		float y;
	};

	int tmp;
	int line;
	int fNumber;
	float vx;
	float vy;
	float rotate;
	int count;
	int barrel1;
	int animCnt;
	int anim[3];
	int fBarrel;
	bool fallFlag = false;
public:
	Barrel(Donkey*,HitCheck*,Map*,Player*);
	~Barrel();

	void Init();
	void Update();
	void Draw();

	Map* map;
	HitCheck* hitCheck;
	Donkey* donkey;
	Player* player;

	int removeFlag;
	int floorFlag;
	Vec2 pos;
	Vec2 ftpos;
	
};
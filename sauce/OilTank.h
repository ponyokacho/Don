#pragma once
#include<vector>
class Enemy;
class HitCheck;
class Map;
class Player;
class OilTank {
private:
	struct Vec2 {
		float x;
		float y;
	};
	int oil;
	int tmp;
	int count;
	int fireFlag;
	int fire[2];
	Enemy* enemy;
	std::vector<Enemy*> enemyVec;
public:
	OilTank(HitCheck*, Map*,Player*);
	~OilTank();

	void Init();
	void Update();
	void Draw();


	HitCheck* hitCheck;
	Map* map;
	Player* player;

	Vec2 pos;
	int enemyFlag;
};
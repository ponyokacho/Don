#pragma once
class Map;
class HitCheck;
class Player;
class Enemy {
private:
	struct Vec2 {
		float x;
		float y;
	};
	Vec2 pos;
	int tmp;
	int floorFlag;
	int line;
	int wallFlag;		// 0の時左端、1の時右端
	float vx;
	float vy;
	int count;
	int animSpeed;
	int enemyAnim[3];

public:
	Enemy(HitCheck*,Map*,Player*);
	~Enemy();

	HitCheck* hitCheck;
	Map* map;
	Player* player;

	int removeFlag;
	void Init();
	void Update();
	void Draw();
};
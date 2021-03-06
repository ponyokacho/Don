#pragma once

class HitCheck;
class Map;

class Player {
private:

	struct Vec2 {
		float x;
		float y;
	};

	int tmp;
	int animCount;
	int deathCount;
	int lrFlag;		// -1:左 1:右
	int walkFlag;	// 0:止 1:動
	int lWalk[2];
	int rWalk[2];
	int ladder[2];
	int deathRoll[4];
	int udFlag;
	float vy;
	int line;
	int count = 120;

	
public:
	Player(HitCheck*,Map*);
	~Player();

	int floorFlag;	// 階層フラグ(0から6まで)上り途中は-1
	int deathFlag;	// 死亡フラグ 0:生 1:死 -1:ｹﾞｰﾑｵｰﾊﾞｰへ
	int clearFlag;

	int jumpFlag;
	Vec2 pos;
	HitCheck* hitCheck;
	Map* map;


	void Init();
	void Update();
	void Draw();

};
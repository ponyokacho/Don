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
	int lrFlag;		// -1:�� 1:�E
	int walkFlag;	// 0:�~ 1:��
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

	int floorFlag;	// �K�w�t���O(0����6�܂�)���r����-1
	int deathFlag;	// ���S�t���O 0:�� 1:�� -1:�ްѵ��ް��
	int clearFlag;

	int jumpFlag;
	Vec2 pos;
	HitCheck* hitCheck;
	Map* map;


	void Init();
	void Update();
	void Draw();

};
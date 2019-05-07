#pragma once
class Player;
class Peach {
private:
	int tmp;
	int count;
	int moveFlag;
	int animCount;
	int AnimCnt[2];
	int love;
	struct Vec2 {
		float x;
		float y;
	};
	Vec2 pos;
public:
	Peach(Player*);
	~Peach();

	Player* player;

	void Init();
	void Update();
	void Draw();
};
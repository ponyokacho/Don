#pragma once

#include <vector>
class Map;
class HitCheck;
class Donkey;
class Peach;
class Barrel;
class OilTank;
class Player;

class GameTask
{
private:
	// ----- ｺﾝｽﾄﾗｸﾀ群
	GameTask() {}	// ﾃﾞﾌｫﾙﾄｺﾝｽﾄﾗｸﾀをprivateにして外部から生成できない様にする
	GameTask(const GameTask&) {}					// ----- ｺﾋﾟｰｺﾝｽﾄﾗｸﾀをprivate化
	GameTask& operator=(const GameTask&) {}		// ----- 代入演算子のｵｰﾊﾞｰﾗｲﾄﾞをprivate化
	~GameTask() {}	// ﾃﾞｽﾄﾗｸﾀ

	// 画面遷移用
	enum GAME_MODE {
		GAME_INIT,
		GAME_TITLE,
		GAME_MAIN,
		GAME_OVER,
	};
	GAME_MODE gameMode;

	int GameInit(void);
	int GameTitle(void);
	int GameMain(void);
	int GameOver(void);

	int newKey;
	int oldKey;
	int trgKey;

	// 配列番号保持用
	int tmpI;
	int tmpJ;

	int breakFlag;

	// ｹﾞｰﾑﾙｰﾌﾟ用関数ﾎﾟｲﾝﾀｰ
	//int (GameTask::*gLoopPtr)(void);

	Map* map;
	HitCheck* hit;
	Donkey* donkey;
	Peach* peach;
	Barrel* barrel;
	OilTank* oil;
	Player* player;

	//--- vector
	std::vector<Barrel*>barrelVec;

public:
	static int SCREEN_SIZE_X;
	static int SCREEN_SIZE_Y;

	int ObjCnt;

	void addObjCnt();
	void removeObjCnt();

	int SystemInit(void);
	static GameTask &GetInstance(void) {
		static GameTask gInstance;	// GameTaskの実体を生成。gInstanceに保存する
		return gInstance;
	}
	int Update(void);
	int animCnt;

	int barrel1;
};
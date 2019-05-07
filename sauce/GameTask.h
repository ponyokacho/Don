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
	// ----- �ݽ�׸��Q
	GameTask() {}	// ��̫�ĺݽ�׸���private�ɂ��ĊO�����琶���ł��Ȃ��l�ɂ���
	GameTask(const GameTask&) {}					// ----- ��߰�ݽ�׸���private��
	GameTask& operator=(const GameTask&) {}		// ----- ������Z�q�̵��ްײ�ނ�private��
	~GameTask() {}	// �޽�׸�

	// ��ʑJ�ڗp
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

	// �z��ԍ��ێ��p
	int tmpI;
	int tmpJ;

	int breakFlag;

	// �ް�ٰ�ߗp�֐��߲���
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
		static GameTask gInstance;	// GameTask�̎��̂𐶐��BgInstance�ɕۑ�����
		return gInstance;
	}
	int Update(void);
	int animCnt;

	int barrel1;
};
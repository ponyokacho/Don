#include <DxLib.h>
#include "HitCheck.h"
#include "Map.h"
#include "OilTank.h"
#include "Enemy.h"
#include "Player.h"

OilTank::OilTank(HitCheck* hit,Map* m,Player* p)
{
	hitCheck = hit;
	map = m;
	player = p;
	Init();
}

OilTank::~OilTank()
{
}

void OilTank::Init()
{
	oil = LoadGraph("image/Donkey Kong_OIL02.png");
 	tmp = LoadGraph("image/fireAnim.png");
	fire[0] = DerivationGraph(0, 0, 16, 9, tmp);
	fire[1] = DerivationGraph(16, 0, 16, 9, tmp);
	enemyFlag = false;
	fireFlag = false;

	pos.x = 31;
	pos.y = 330;
}

void OilTank::Update()
{
	count++;
	std::vector<Enemy*>::iterator itr = enemyVec.begin();
	if (enemyFlag == true)
	{
		enemyFlag = false;
		fireFlag = true;
		enemy = new Enemy(hitCheck,map,player);
		enemyVec.push_back(enemy);
	}

	for (itr = enemyVec.begin(); itr != enemyVec.end(); itr++)
	{
		(*itr)->Update();
		(*itr)->Draw();
	}
	//--- çÌèú
	itr = enemyVec.begin();
	while (itr != enemyVec.end()) {
		if ((*itr)->removeFlag == true) {
			delete (*itr);				// é¿ëÃÇè¡Ç∑
			itr = enemyVec.erase(itr);	// ÿΩƒÇè¡Ç∑
			break;
		}
		else {
			itr++;
		}
	}
}

void OilTank::Draw()
{
	if (fireFlag == true)
	{
		DrawGraph(pos.x, pos.y - 9, fire[count / 10 % 2], true);
	}
	DrawGraph(pos.x,pos.y, oil, true);
}

#include <DxLib.h>
#include "GameTask.h"
#include "KeyMng.h"
#include "HitCheck.h"
#include "Map.h"
#include "Donkey.h"
#include "Peach.h"
#include "Barrel.h"
#include "OilTank.h"
#include "Player.h"

// 10*10 X:26,Y:28
int GameTask::SCREEN_SIZE_X = 310;
int GameTask::SCREEN_SIZE_Y = 360;

void GameTask::addObjCnt()
{
	ObjCnt++;
}

void GameTask::removeObjCnt()
{
	ObjCnt--;
}

int GameTask::SystemInit()
{
	SetWindowText("1701331_‘D•x");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);	// 1024~600ÄŞ¯Ä32bit‚Éİ’è
	ChangeWindowMode(true);				// true:window@false:ÌÙ½¸Ø°İ
	SetWindowSize(620, 760);
	if (DxLib_Init() == -1) {
		return false;					// DX×²ÌŞ×Ø‰Šú‰»ˆ—
	}

	gameMode = GAME_INIT;
	return 0;
}

int GameTask::GameInit()
{
	map = new Map();
	hit = new HitCheck();
	donkey = new Donkey();
	player = new Player(hit,map);
	peach = new Peach(player);
	oil = new OilTank(hit,map,player);

	tmpI = 2;
	tmpJ = 0;

	breakFlag = false;
	return 0;
}
// ========== À²ÄÙ‰æ–Ê‚Ìˆ—
int GameTask::GameTitle()
{
	SetFontSize(10);
	DrawFormatString(70, 0, 0xff0000, "‚P‚t‚o");
	DrawFormatString(150, 0, 0xff0000, "‚g‚h‚f‚g@‚r‚b‚n‚q‚d");
	// ƒXƒRƒA•\¦
	DrawFormatString(55, 10, 0xffffff, "‚O‚O‚O‚O‚O‚O");
	DrawFormatString(170, 10, 0xffffff, "‚O‚O‚O‚O‚O‚O");
	DrawFormatString(90, 70, 0x00ffff, "‚h‚m‚r‚d‚q‚s@‚b‚n‚h‚m");
	DrawFormatString(45, 80, 0x00ffff, "(‚o‚q‚d‚r‚r@‚r‚o‚`‚b‚d@‚a‚t‚s‚s‚n‚m)");
	/*if (trgKey[_1START] || CheckHitKey(KEY_INPUT_SPACE))
	{
		gameMode = GAME_MAIN;
	}*/
	//DrawString(0, 0, "TITLE", 0xffff00);
	return 0;
}

// ========== ¹Ş°ÑÒ²İˆ—
int GameTask::GameMain()
{
	//DrawString(0, 0, "MAIN", 0xffff00);

	std::vector<Barrel*>::iterator itr = barrelVec.begin();

	// ’M‚Ì¶¬
	if (donkey->throwFlag == true)
	{
		barrel = new Barrel(donkey,hit,map,player);
		barrelVec.push_back(barrel);
	}

	// Draw,UpdateŒn
	map->Draw();
	if (player->clearFlag == false)
	{
		peach->Update();
	}
	peach->Draw();
	donkey->Update();
	donkey->Draw();
	for (itr = barrelVec.begin(); itr != barrelVec.end(); ++itr)		// itr§Œä‚Ì‚É‚Í++itr
	{
		(*itr)->Update();
		(*itr)->Draw();
	}
	oil->Update();
	oil->Draw();
	if (player->deathFlag == false)
	{
		player->Update();
	}
		player->Draw();

	//--- íœ
	itr = barrelVec.begin();
	while (itr != barrelVec.end()) {
		if ((*itr)->removeFlag == true) {	
			oil->enemyFlag = true;
			delete (*itr);				// À‘Ì‚ğÁ‚·
			itr = barrelVec.erase(itr);	// Ø½Ä‚ğÁ‚·
			break;
		}
		else {
			itr++;
			oil->enemyFlag = false;
		}
	}
	// ’òq‚ÆÌßÚ²Ô°
	for (int i = 0; i < 2; i++)
	{
		if (hit->hitCheckLadder(player->pos.x, player->pos.y, map->lPos[i][player->floorFlag].x, map->lPos[i][player->floorFlag].y))
		{
			break;
		}
		if (hit->hitCheckLadder(player->pos.x, player->pos.y, map->lPos[i][player->floorFlag-1].x, map->lPos[i][player->floorFlag-1].y))
		{
			break;
		}
	}

	if (player->deathFlag == -1)
	{
		gameMode = GAME_OVER;
	}
	if (player->clearFlag == true)
	{
		gameMode = GAME_OVER;
	}
	
	return 0;
}

// ========== ¹Ş°Ñµ°ÊŞ°ˆ—
int GameTask::GameOver()
{
	DrawFormatString(100, 100, 0xffffff, "ƒQ[ƒ€ƒI[ƒo[");
	DrawFormatString(100, 150, 0xffffff, "½Íß°½ÎŞÀİ‚ğ‰Ÿ‚µ‚½‚çÀ²ÄÙ‰æ–Ê‚ÉB");
	barrelVec.clear();
	if (trgKey)
	{
		gameMode = GAME_INIT;	// À²ÄÙ‰æ–Ê‚Ì‘O‚É¹Ş°Ñ‚Ì‰Šú‰»
	}
	//DrawString(0, 0, "OVER", 0xffff00);
	return 0;
}

int GameTask::Update()
{
	trgKey = 0;
	newKey = 0;

	//DrawFormatString(915, 32, 0xffffff, "ObjCnt = %d", ObjCnt);

	KeyMng::GetInstance().Update();
	//int rtnID = (this->*gLoopPtr)();	// ¹Ş°ÑÙ°Ìß(ŠÖ”Îß²İÀ°)
	//return rtnID;

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		newKey = 1;
	}
	trgKey = ~oldKey & newKey;			// ÄØ¶Ş°·°

	if ((oldKey == 0) && (newKey == 1))
	{
		trgKey = 1;
	}
	oldKey = newKey;

	switch (gameMode) {
	case GAME_INIT:
		GameInit();
		//gLoopPtr = &GameTask::GameMain;
		gameMode = GAME_TITLE;
		break;
	case GAME_TITLE:
		GameTitle();
		if (trgKey)
		{
			//gLoopPtr = &GameTask::GameMain;
			gameMode = GAME_MAIN;
		}
		break;
	case GAME_MAIN:
		GameMain();
		if (trgKey)
		{
			//gLoopPtr = &GameTask::GameMain;
			//gameMode = GAME_OVER;
		}
		break;
	case GAME_OVER:
		GameOver();
		if (trgKey)
		{
			//gLoopPtr = &GameTask::GameMain;
			gameMode = GAME_INIT;
		}
		break;
	default:
		break;
	};
	return 0;
}
#include <DxLib.h>
#include <stdlib.h>
#include "KeyMng.h"
#include "map.h"
#include "HitCheck.h"
#include "Player.h"

Player::Player(HitCheck* hit,Map* m)
{
	hitCheck = hit;
	map = m;
	Init();
}
Player::~Player()
{
}

void Player::Init()
{
	lrFlag = 1;
	walkFlag = 0;
	jumpFlag = false;
	udFlag = false;
	deathFlag = false;
	animCount = 0;
	deathCount = 0;
	pos.x = 31 * 2;
	pos.y = 330;
	vy = 0;
	tmp = LoadGraph("image/Donkey Kong_LMarioT.png");
	lWalk[0] = DerivationGraph(0, 0, 19, 21, tmp);
	lWalk[1] = DerivationGraph(19, 0, 19, 21, tmp);
	tmp = LoadGraph("image/Donkey Kong_RMarioT.png");
	rWalk[0] = DerivationGraph(0, 0, 19, 21, tmp);
	rWalk[1] = DerivationGraph(19, 0, 19, 21, tmp);
	tmp = LoadGraph("image/Donkey Kong_HMarioT.png");
	ladder[0] = DerivationGraph(0, 0, 20, 20, tmp);
	ladder[1] = DerivationGraph(20, 0, 20, 20, tmp);
	tmp = LoadGraph("image/mRolling.png");
	for(int i = 0; i < 4; i++)
	{
		deathRoll[i] = DerivationGraph(26 * i, 0, 26, 22, tmp);
	}

	tmp = LoadGraph("image/death.png");
}

void Player::Update()
{
	//DrawFormatString(100, 0, 0xffffff, "pos.x=%f,pos.y=%f", pos.x, pos.y);
	//DrawFormatString(10, 0, 0xffffff, "%d", jumpFlag);
	animCount++;
	pos.y += vy;
	// ｼﾞｬﾝﾌﾟ
	if (jumpFlag == false)
	{
		if (KeyMng::GetInstance().trgKey[P1_SPACE])
		{
			vy = -2.0f;
		}
	}
	if (vy != 0)
	{
		jumpFlag = true;
	}
	vy += 0.1f;
	// 当たり判定処理
	// 足場とﾌﾟﾚｲﾔｰ
	for (int i = 0; i < 10; i++)
	{
		if (hitCheck->hitCheckUD(pos.x, pos.y, map->fPos[i][floorFlag].x, map->fPos[i][floorFlag].y))
		{
 			pos.y = map->fPos[i][floorFlag].y - 21;
 			jumpFlag = false;
			break;
		}
	}

	//----------移動
	// 左へ移動
	if (KeyMng::GetInstance().newKey[P1_LEFT])
	{
		lrFlag = -1;
		walkFlag = 1;
		pos.x -= 1.5f;
		if (pos.x <= 0)
		{
			pos.x = 0;
		}
	}
	// 右へ移動
	else if (KeyMng::GetInstance().newKey[P1_RIGHT])
	{
		lrFlag = 1;
		walkFlag = 1;
		pos.x += 1.5f;
		if (pos.x >= 310 - 19)
		{
			pos.x = 310 - 19;
		}
	}
	else
	{
		walkFlag = 0;
	}
	//----------梯子
	for (int i = 7; i > 0; i--)
	{
		line = 50 * i;
		//DrawLine(0, line, 310,line, 0xffffff, 1);
		int posY = pos.y;
		if (posY < line && posY >= line - 38)		// 本来line-38だが、小数の差で通ってしまうため37にする。
		{
			floorFlag = abs(i - 7);
		}
	}
	if (hitCheck->ladderFlag == true)
	{
		vy = 0;
		// 梯子を上る
		if (KeyMng::GetInstance().newKey[P1_UP])
		{
			udFlag = true;
			pos.y -= 0.5;
		}
		// 梯子を下る
		else if (KeyMng::GetInstance().newKey[P1_DOWN])
		{
			udFlag = true;
			if (hitCheck->groundFlag == false)
			{
				pos.y += 0.5;
			}
		}
		else 
		{
			udFlag = false;
		}
	}
	if (pos.y < 40)
	{
		clearFlag = true;
	}
}

void Player::Draw()
{
	if (deathFlag == false)
	{
		if (hitCheck->ladderFlag == 1 && udFlag == true)
		{
			DrawGraph(pos.x, pos.y, ladder[animCount / 5 % 2], true);
		}
		else if (walkFlag == 1)
		{
			if (lrFlag == -1)
			{
				DrawGraph(pos.x, pos.y, lWalk[animCount / 3 % 2], true);
			}
			else if (lrFlag == 1)
			{
				DrawGraph(pos.x, pos.y, rWalk[animCount / 3 % 2], true);
			}
		}
		else
		{
			animCount = 0;
			if (hitCheck->ladderFlag == 1 && udFlag == false)
			{
				DrawGraph(pos.x, pos.y, ladder[0], true);
			}
			else if (lrFlag == -1)
			{
				DrawGraph(pos.x, pos.y, lWalk[0], true);
			}
			else if (lrFlag == 1)
			{
				DrawGraph(pos.x, pos.y, rWalk[1], true);
			}
		}
	}
	else
	{
		deathCount++;
		if (deathCount <= 80)
		{
			DrawGraph(pos.x, pos.y, deathRoll[deathCount / 5 % 4], true);
		}
		else if(deathCount <= 140)
		{
			DrawGraph(pos.x, pos.y, tmp, true);
		}
		else
		{
			deathFlag= -1;
		}
	}
}

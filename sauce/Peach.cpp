#include <DxLib.h>
#include "Player.h"
#include "Peach.h"

Peach::Peach(Player* p)
{
	player = p;
	Init();
}

Peach::~Peach()
{
}

void Peach::Init()
{
	moveFlag = false;
	animCount = 0;
	count = 0;
	pos.x = 100;
	pos.y = 34;
	tmp = LoadGraph("image/Donkey Kong_Peach01.png");
	AnimCnt[0] = DerivationGraph(0, 0, 25, 31, tmp);
	AnimCnt[1] = DerivationGraph(25, 0, 25, 31, tmp);
	love = LoadGraph("Donkey Kong_Peach02.png");
}

void Peach::Update()
{
	if (player->clearFlag == false)
	{
		count++;
		if (count >= 150 && count <= 210)
		{
			moveFlag = true;
		}
		else if (count > 210)
		{
			count = 0;
			animCount = 0;
			moveFlag = false;
		}
		else
		{
			moveFlag = false;
		}
	}
}

void Peach::Draw()
{
	if (player->clearFlag == false)
	{
		animCount++;
		if (moveFlag == true)
		{
			DrawGraph(pos.x, pos.y, AnimCnt[animCount / 10 % 2], true);
		}
		else
		{
			DrawGraph(pos.x, pos.y, AnimCnt[1], true);
		}
	}
	else
	{
		DrawGraph(pos.x, pos.y, love, true);
	}
}

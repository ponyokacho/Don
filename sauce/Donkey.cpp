#include <DxLib.h>
#include "Donkey.h"


Donkey::Donkey()
{
	Init();
}

Donkey::~Donkey()
{
}

void Donkey::Init()
{
	tmp = LoadGraph("image/firstThrow.png");
	for (int i = 0; i < 3; i++)
	{
		firstThrow[i] = DerivationGraph(i * 58, 0, 58, 39, tmp);
	}
	tmp = LoadGraph("image/Donkey Kong_DonkeyFull.png");
	for (int i = 0; i < 6; i++)
	{
		AnimCnt[i] = DerivationGraph(i * 58, 0, 58, 39, tmp);
	}

	count = 0;
	countF = 0;
	throwCnt = 0;
	throwFlag = false;
	barrelFlag = false;
	ftFlag = false;
	ftAnimFlag = true;
}

void Donkey::Update()
{
	countF++;
	if (countF <= 90)
	{
		if (countF == 60)
		{
			throwFlag = true;
			ftFlag = true;
		}
		else
		{
			throwFlag = false;
		}
		if (countF >= 90)
		{
			ftAnimFlag = false;
		}
	}
	else
	{
		count++;
		if (count == 120)
		{
			throwFlag = true;
		}
		else if (count > 150)
		{
			count = 0;
			throwFlag = false;
		}
		else
		{
			throwFlag = false;
		}
	}
}

void Donkey::Draw()
{
	if (ftAnimFlag == false)
	{
		DrawGraph(38, 70, AnimCnt[count / 30 % 5], true);
	}
	else
	{
		DrawGraph(38, 70, firstThrow[countF / 30 % 3], true);
	}
}

#include <Dxlib.h>
#include "HitCheck.h"

HitCheck::HitCheck()
{
	Init();
}

HitCheck::~HitCheck()
{
}

void HitCheck::Init()
{
	tmp = LoadSoftImage("image/SFrame.png");
	fHitFlag = false;
	groundFlag = false;
	ladderFlag = false;
	test = 10;
}

// 関数まとめる
int HitCheck::hitCheckUD(float playerX, float playerY, float frameX, float frameY)
{
	Corn player;
	Corn frame;
	player.L = playerX;		// 当たり判定の調整
	player.R = playerX + 19;
	player.U = playerY;
	player.D = playerY + 21;

	frame.L = frameX;
	frame.R = frameX + 31;
	frame.U = frameY;
	frame.D = frameY + 12;

	//DrawBox(player.L, player.U, player.R, player.D, 0xff0000, false);
	//DrawBox(frame.L, frame.U, frame.R, frame.D, 0x00ff00, false);
	// DrawBox挟まないと判定が取れない謎
	DrawBox(0, 0, 0, 0, 0x000000,false);

	if (player.L < frame.R && player.R > frame.L)
	{
		if (ladderFlag == false)
		{
			// 地面判定
			if (player.D > frame.U)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

}

int HitCheck::hitCheckLR(float playerX, float playerY, float frameX, float frameY)
{
	Corn player;
	Corn frame;

	player.L = playerX;
	player.R = playerX + 19;
	player.U = playerY;
	player.D = playerY + 21; 

	frame.L = frameX;
	frame.R = frameX + 31;
	frame.U = frameY;
	frame.D = frameY + 12;

	//DrawBox(player.L, player.U, player.R, player.D, 0xff0000, false);

	if (player.D < frame.U && player.U > frame.D)
	{
		if (player.L < frame.R)
		{
			return true;
		}
		if (player.R > frame.L)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}


int HitCheck::hitCheckLadder(float playerX, float playerY, float ladderX, float ladderY)
{
	Corn player;
	Corn ladder;

	player.L = playerX;
	player.R = playerX + 19;
	player.U = playerY;
	player.D = playerY + 21;

	ladder.L = ladderX;
	ladder.R = ladderX + 11;
	ladder.U = ladderY - 35;
	ladder.D = ladderY - 5;

	//DrawBox(ladder.L, ladder.U, ladder.R, ladder.D, 0x0000ff, false);
	//DrawBox(player.L, player.U, player.R, player.D, 0xff0000, false);

	if (player.L < ladder.R && player.R > ladder.L && 
		player.D > ladder.U && player.U < ladder.D)
	{
		ladderFlag = true;
		return true;
	}
	else
	{
		ladderFlag = false;
		return false;
	}
	return 0;
}

int HitCheck::hitCheckBarAndFra(float barrelX, float barrelY, float frameX, float frameY)
{
	Corn barrel;
	Corn frame;

	// DrawRotaGraphで0.9倍しているので+4で調整
	barrel.L = barrelX + 4;
	barrel.R = barrelX + 21;
	barrel.U = barrelY + 4;
	barrel.D = barrelY + 21;

	frame.L = frameX;
	frame.R = frameX + 31;
	frame.U = frameY;
	frame.D = frameY + 12;

	//DrawBox(frame.L, frame.U, frame.R, frame.D, 0x00ff00,false);
	//DrawBox(barrel.L, barrel.U, barrel.R, barrel.D, 0xffff00, false);

	if (barrel.L < frame.R && barrel.R > frame.L &&
		barrel.D > frame.U && barrel.U < frame.D)
	{
		return true;
	}
	else
	{
		return false;
	}

	return 0;
}

int HitCheck::hitCheckEneAndFra(float enemyX, float enemyY, float frameX, float frameY)
{
	Corn enemy;
	Corn frame;

	enemy.L = enemyX;
	enemy.R = enemyX + 15;
	enemy.U = enemyY - 3;
	enemy.D = enemyY + 10;

	frame.L = frameX;
	frame.R = frameX + 31;
	frame.U = frameY;
	frame.D = frameY + 12;

	//DrawBox(frame.L, frame.U, frame.R, frame.D, 0x00ff00, false);
	//DrawBox(enemy.L, enemy.U, enemy.R, enemy.D, 0xffff00, false);

	if (enemy.L < frame.R && enemy.R > frame.L &&
		enemy.D > frame.U && enemy.U < frame.D)
	{
		return true;
	}
	else
	{
		return false;
	}

	return 0;
}

int HitCheck::hitCheckBarAndLad(float barrelX, float barrelY, float ladderX, float ladderY,int floor)
{
	Corn barrel;
	Corn ladder;

	if (floor % 2 != 0)
	{
		barrel.L = barrelX;
		barrel.R = barrelX + 10;			// 当たり判定をずらす
	}
	else
	{
		barrel.L = barrelX + 17;
		barrel.R = barrelX + 27;			// 当たり判定をずらす
	}
	barrel.U = barrelY + 5;
	barrel.D = barrelY + 30;

	ladder.L = ladderX;
	ladder.R = ladderX + 11;
	ladder.U = ladderY - 35;
	ladder.D = ladderY - 10;

	//DrawBox(barrel.L, barrel.U, barrel.R, barrel.D, 0x0000ff, false);
	//DrawBox(ladder.L, ladder.U, ladder.R, ladder.D, 0xffff00, false);

	// 当たっている途中で別の梯子に判定が移り、return falseになる。
	if (barrel.L < ladder.R && barrel.R > ladder.L &&
		barrel.D > ladder.U && barrel.U < ladder.D)
	{
		return true;
	}
	else
	{
		return false;
	}

	return 0;
}

int HitCheck::hitCheckBarAndPlayer(float playerX, float playerY, float barrelX, float barrelY)
{
	Corn player;
	Corn barrel;

	barrel.L = barrelX + 4;
	barrel.R = barrelX + 21;
	barrel.U = barrelY + 4;
	barrel.D = barrelY + 21;

	player.L = playerX;
	player.R = playerX + 19;
	// 上下判定小さめ
	player.U = playerY + 7;
	player.D = playerY + 21 - 7;

	//DrawBox(player.L, player.U, player.R, player.D, 0xff0000, false);
	//DrawBox(barrel.L, barrel.U, barrel.R, barrel.D, 0x0000ff, false);

	if (player.L < barrel.R && player.R > barrel.L &&
		player.D > barrel.U && player.U < barrel.D)
	{
		return true;
	}
	else
	{
		return false;
	}

	return 0;
}
int HitCheck::hitCheckPlayerAndEnemy(float playerX, float playerY, float enemyX, float enemyY)
{
	Corn player;
	Corn enemy;

	enemy.L = enemyX;
	enemy.R = enemyX + 15;
	enemy.U = enemyY - 3;
	enemy.D = enemyY + 10;

	player.L = playerX;
	player.R = playerX + 19;
	// 上下判定小さめ
	player.U = playerY + 7;
	player.D = playerY + 21 - 7;

	//DrawBox(player.L, player.U, player.R, player.D, 0xff0000, false);
	//DrawBox(enemy.L, enemy.U, enemy.R, enemy.D, 0xffff00, false);

	if (player.L < enemy.R && player.R > enemy.L &&
		player.D > enemy.U && player.U < enemy.D)
	{
		return true;
	}
	else
	{
		return false;
	}

	return 0;
}


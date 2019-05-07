#include <Dxlib.h>
#include "Map.h"
#include "HitCheck.h"
#include "Player.h"
#include "Enemy.h"

Enemy::Enemy(HitCheck* hit, Map* m,Player* p)
{
	hitCheck = hit;
	map = m;
	player = p;
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	pos.x = 32;
	pos.y = 330;
	vx = 0;
	vy = 0;
	count = 0;
	wallFlag = 0;
	tmp = LoadGraph("image/enemyAnim.png");
	for (int i = 0; i < 3; i++)
	{
		enemyAnim[i] = DerivationGraph(15 * i, 0, 15, 15, tmp);
	}
	removeFlag = false;
}

void Enemy::Update()
{
	pos.x += vx;
	pos.y += vy;
	for (int i = 7; i > 0; i--)
	{
		line = 40 * i;
		//DrawLine(0, line, 310, line, 0xffffff, 1);
		int posY = pos.y;			// intŒ^‚É•ÏŠ·
		if (posY < line && posY >= line - 21)
		{
			floorFlag = abs(i - 7);
		}
	}
	count++;
	animSpeed = (count / 1 % 3);
	if (count <= 20)
	{
		vx = 0.5;
		vy = -0.5;
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (hitCheck->hitCheckEneAndFra(pos.x, pos.y, map->fPos[i][floorFlag].x, map->fPos[i][floorFlag].y))
			{
				vy = 0.05;
				pos.y = map->fPos[i][floorFlag].y - 10 + vy;
				if (wallFlag == 0)
				{
					if (GetRand(100) % 3 == 0)
					{
						vx = -1;
						if (pos.x <= 0)
						{
							pos.x = 0;
							wallFlag = 0;
						}
					}
					else
					{
						vx = 1;
						if (pos.x >= 310 - 15)
						{
							pos.x = 310 - 15;
							wallFlag = 1;
						}
					}
					break;
				}
				else
				{
					if (GetRand(100) % 3 == 0)
					{
						vx = 1;
						if (pos.x <= 0)
						{
							pos.x = 0;
							wallFlag = 0;
						}
					}
					else
					{
						vx = -1;
						if (pos.x >= 310 - 15)
						{
							pos.x = 310 - 15;
							wallFlag = 1;
						}
					}
					break;
				}
			}
			else
			{
				pos.y += vy;
				vy = 0.05;
			}
		}
		if (hitCheck->hitCheckPlayerAndEnemy(player->pos.x, player->pos.y, pos.x, pos.y))
		{
			player->deathFlag = true;
		}
	}

}

void Enemy::Draw()
{
	if (wallFlag == 0)
	{
		DrawGraph(pos.x, pos.y - 5, enemyAnim[animSpeed], true);
	}
	else
	{
		DrawTurnGraph(pos.x, pos.y - 5, enemyAnim[animSpeed], true);
	}
}

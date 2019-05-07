#include <DxLib.h>
#include "Map.h"
#include "HitCheck.h"
#include "Barrel.h"
#include "Donkey.h"
#include "Player.h"

constexpr float PAI = 3.1415;

Barrel::Barrel(Donkey* don,HitCheck* hit,Map* m,Player* p)
{
	donkey = don;
	hitCheck = hit;
	map = m;
	player = p;
	Init();
}

Barrel::~Barrel()
{
}

void Barrel::Init()
{
	barrel1 = LoadGraph("image/Donkey Kong_BarrelAnim.png");
	barrel1 = DerivationGraph(0, 3, 21, 21, barrel1);
	fBarrel = LoadGraph("image/Donkey Kong_Barrel.png");
	count = 0;
	pos.x = 80;
	pos.y = 90;
	ftpos.x = 53;
	ftpos.y = 90;
}

void Barrel::Update()
{
	//*ÏØµ‚æ‚è‰º‚ÌŠK‘w‚Ì’M‚Í’[‚©‚ç—‚Æ‚·
	if (donkey->ftFlag == false)
	{
		rotate = count * (PAI / 180);
		pos.x += vx;
		for (int i = 7; i > 0; i--)
		{
			line = 51 * i;
			//DrawLine(0, line, 310, line, 0xffffff, 1);
			int posY = pos.y;			// intŒ^‚É•ÏŠ·
			if (posY < line && posY >= line - 21)
			{
				floorFlag = abs(i - 7);
			}
		}
		
		if (fallFlag == false)
		{
			if (floorFlag % 2 == 0)
			{
				count -= 10;
				vx = -1.5;
			}
			else
			{
				count += 10;
				vx = 1.5;
			}
		}
		else
		{
			// ’M‚ğ’òq‚©‚ç—‚Æ‚·
			vx = 0;
		}

		//----------“–‚½‚è”»’è(’M‚Æ‘«ê)
		for (int i = 0; i < 10; i++)
		{
			if (fallFlag == false)
			{		
				if (hitCheck->hitCheckBarAndFra(pos.x, pos.y, map->fPos[i][floorFlag].x, map->fPos[i][floorFlag].y))
				{
					vy = 0.2;
					pos.y = map->fPos[i][floorFlag].y - 21 + vy;
					break;
				}
				else
				{
					//hitCheck->fHitFlag = false;
					pos.y += vy;
					vy = 0.3;
				}
			}
			else
			{
				if (hitCheck->hitCheckBarAndFra(pos.x, pos.y, map->fPos[i][floorFlag-1].x, map->fPos[i][floorFlag-1].y))
				{
					fallFlag = false;
				}
				else
				{
					vy = 0.1;
					pos.y += vy;
				}
			}
		}
	}
	else
	{
		ftpos.y += vy;
		//----------“–‚½‚è”»’è(1”Ô–Ú‚Ì’M‚Æ1”Ô‰º‚Ì‘«ê)
		for (int i = 0; i < 10; i++)
		{
			if (hitCheck->hitCheckBarAndFra(ftpos.x, ftpos.y, map->fPos[i][0].x, map->fPos[i][0].y))
			{
				donkey->ftFlag = false;
				pos.x = ftpos.x;
				pos.y = ftpos.y;
				break;
			}
			else
			{
				ftpos.y += vy;
				vy = 0.3;
			}
		}
	}
	
	// “–‚½‚è”»’è(’M‚Æ’òq)
	for(int i = 0; i < 2; i++)
	{
		if (hitCheck->hitCheckBarAndLad(pos.x, pos.y, map->lPos[i][floorFlag - 1].x, map->lPos[i][floorFlag - 1].y,floorFlag))
		{
			if (hitCheck->fHitFlag == false)
			{
				// pos.x = 0‚É‚µ‚Ä,Œ»İ‚Ì°‚Ì“–‚½‚è”»’è‚ğ1ŠK‘w‰º‚É‚·‚éB
				hitCheck->fHitFlag = true;
				fallFlag = true;
				break;
			}
		}
		else
		{
			hitCheck->fHitFlag = false;
			break;
		}
	}
	// “–‚½‚è”»’è(’M‚ÆÌßÚ²Ô°)
	if (hitCheck->hitCheckBarAndPlayer(player->pos.x, player->pos.y, pos.x, pos.y))
	{
		player->deathFlag = true;
	}

	if (pos.x < 30 && pos.y > 300)
	{
		removeFlag = true;
		hitCheck->fHitFlag = false;
	}
	else
	{
		removeFlag = false;
	}
}

void Barrel::Draw()
{
	if (fallFlag == false)
	{
		if (donkey->ftFlag == false)
		{
			//DrawBox(pos.x + 4, pos.y + 4, pos.x + 21, pos.y + 21, 0xff00ff, false);
			DrawRotaGraph(pos.x + 13, pos.y + 13, 0.9, rotate, barrel1, true);
		}
		else
		{
			DrawGraph(ftpos.x, ftpos.y, fBarrel, true);
		}
	}
	else
	{
		DrawRotaGraph(pos.x + 13, pos.y + 13, 0.9, 0, fBarrel, true);
	}
}

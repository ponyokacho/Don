#pragma once

typedef enum
{
	_1UP,
	_1DOWN,
	_1RIGHT,
	_1LEFT,
	_1A,
	_1B,
	_1X,
	_1Y,
	_1L,
	_1R,
	_1SELECT,
	_1START,	// 12
	KEY_MAX
}KEY_CODE;

// ---------- 変数の宣言
extern int trgKey[KEY_MAX];	// ﾄﾘｶﾞｷｰ
extern int newKey[KEY_MAX];	// 今回ﾙｰﾌﾟ時の入力状態
extern int oldKey[KEY_MAX];	// 前回ﾙｰﾌﾟ時の入力状態
extern int upKey[KEY_MAX];	// ｷｰｱｯﾌﾟしたｷｰのﾁｪｯｸ

// ---------- 関数ﾌﾟﾛﾄﾀｲﾌﾟ宣言
void CheckKey();
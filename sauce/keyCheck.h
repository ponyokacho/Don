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

// ---------- �ϐ��̐錾
extern int trgKey[KEY_MAX];	// �ض޷�
extern int newKey[KEY_MAX];	// ����ٰ�ߎ��̓��͏��
extern int oldKey[KEY_MAX];	// �O��ٰ�ߎ��̓��͏��
extern int upKey[KEY_MAX];	// �����߂�����������

// ---------- �֐��������ߐ錾
void CheckKey();
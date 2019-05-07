#include "DxLib.h"
#include "keyCheck.h"

int trgKey[KEY_MAX];	// �ض޷�
int newKey[KEY_MAX];	// ����ٰ�ߎ��̓��͏��
int oldKey[KEY_MAX];	// �O��ٰ�ߎ��̓��͏��
int upKey[KEY_MAX];	// �����߂�����������

void CheckKey()
{
	struct {
		int kinput;	// ���ް��
		int jinput;	// �߯��
		KEY_CODE type;	// ���췰����
	}keyTypes[] = {
		// ���ް��,�@�@�@�@ �߯��,�@�@�@�@�@��������
		{ KEY_INPUT_UP,		PAD_INPUT_UP,		_1UP },
		{ KEY_INPUT_DOWN,	PAD_INPUT_DOWN,		_1DOWN },
		{ KEY_INPUT_RIGHT,	PAD_INPUT_RIGHT,	_1RIGHT },
		{ KEY_INPUT_LEFT,	PAD_INPUT_LEFT,		_1LEFT },
		{ KEY_INPUT_X,		PAD_INPUT_B,		_1B },
		{ KEY_INPUT_Z,		PAD_INPUT_A,		_1A },
		{ KEY_INPUT_S,		PAD_INPUT_C,		_1X },
		{ KEY_INPUT_A,		PAD_INPUT_X,		_1Y },
		{ KEY_INPUT_Q,		PAD_INPUT_Y,		_1L },
		{ KEY_INPUT_W,		PAD_INPUT_Z,		_1R },
		{ KEY_INPUT_V,		PAD_INPUT_L,		_1SELECT },
		{ KEY_INPUT_SPACE,	PAD_INPUT_R,		_1START }, // 12
	};

	// �O�񷰓��͍쐬&�ر
	for (int i = 0; i < KEY_MAX; i++) {
		oldKey[i] = newKey[i];	// �O���ڰѓ��͍쐬
		newKey[i] = 0; // ������͸ر
	}

	// �ޮ��߯�ޓ��͏o���邩����
	int padNum = GetJoypadNum();
	int key[2];
	key[0] = GetJoypadInputState(DX_INPUT_PAD1);
	key[1] = GetJoypadInputState(DX_INPUT_PAD2);

	if (padNum == 0) {
		key[0] = 0;
		key[1] = 0;
	}	// �߯�ނ��Ȃ������ꍇ�̏���
	if (padNum == 1) {
		key[1] = 0;
	}

	// ������
	for (int i = 0; i < KEY_MAX; i++) {
		if ((CheckHitKey(keyTypes[i].kinput))
			|| (key[i / 12] & keyTypes[i].jinput)
			) {
			newKey[keyTypes[i].type] |= 1;	// �����߯�ނ̂ǂ��炩�����͂���Ă������׸ނ�1�ɁE�E
		}
		trgKey[keyTypes[i].type] = ~oldKey[keyTypes[i].type] & newKey[keyTypes[i].type];	// �ض�
		upKey[keyTypes[i].type] = oldKey[keyTypes[i].type] & ~newKey[keyTypes[i].type];		// ���߷�
	}

	// �@���ʂ̓���			-> newKey[������]�œ�������
	// �A�ضޓ���			-> trgKey[������]�œ�������
	// �B�����߂���������	-> upKey[������]�œ�������
}
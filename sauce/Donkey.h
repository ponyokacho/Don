#pragma once

class Donkey {
private:
	int tmp;
	int count;
	int countF;
	int ftAnimFlag;		// ������Ұ��ݗp�׸�
	int barrelFlag;
	int BeforeGameAnimCnt[2];
	int firstThrow[3];
	int AnimCnt[6];
public:
	Donkey();
	~Donkey();
	void Init();
	void Update();
	void Draw();

	int throwFlag;
	int throwCnt;
	int ftFlag;		// �����׸�
};
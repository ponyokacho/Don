#pragma once

class HitCheck {
private:
	int tmp;
	typedef struct {
		float L;
		float R;
		float U;
		float D;
	}Corn;
public:
	HitCheck();
	~HitCheck();

	int test;

	int fHitFlag;	// ΜΧΈή
	int groundFlag;
	int ladderFlag;	// -1:Ί 0:~ 1:γ

	void Init();
	int hitCheckUD(float, float, float, float);
	int hitCheckLR(float, float, float, float);
	int hitCheckLadder(float, float, float, float);
	int hitCheckBarAndFra(float, float, float, float);
	int hitCheckEneAndFra(float, float, float, float);
	int hitCheckBarAndLad(float, float , float , float,int);
	int hitCheckBarAndPlayer(float,float,float,float);
	int hitCheckPlayerAndEnemy(float,float,float,float);
	int hitCheckEneAndLad(float, float, float, float);
};
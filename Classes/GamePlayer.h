#pragma once
#include "GameObject.h";

enum CHARATYPE
{
	CHARATYPE_REIMU = 0,
	CHARATYPE_MARISA
};

class GamePlayer
{
private:
	GameObject * m_Characters[2];
	float m_fX;
	float m_fY;

public:
	GamePlayer();
	~GamePlayer();

	void InitPlayer();

	void SetPosition(int IN_fX, int IN_fY);
	Vec2 GetPosition();

	bool MoveTo(int IN_fDestX, int IN_fDestY);

	GameObject * GetCurrentCharacter();
	int ChangePlayer();

	int m_iLives;
	int m_iCurrentPlayer;		//0 : 레이무, 1 : 마리사
	int m_iAbilityEnergy;
	bool m_bCharaChange;
	bool m_bMoving;

};
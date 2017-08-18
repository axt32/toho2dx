#pragma once
#include "GameBaseObject.h"

enum CHARATYPE
{
	CHARATYPE_REIMU = 0,
	CHARATYPE_MARISA
};

#define PLAYERSIZE_RADIUS 75		//넉넉하게 잡음.
#define HEATBOX_RADIUS 5

class GamePlayer
{
private:
	GameBaseObject * m_Characters[2];

public:
	GamePlayer();
	~GamePlayer();

	void InitPlayer();

	void SetPosition(int IN_fX, int IN_fY);
	Vec2 GetPosition();

	GameBaseObject * GetCurrentCharacter();
	GameBaseObject * GetCharacter(CHARATYPE IN_iType);
	int ChangePlayer();

	cocos2d::Layer * m_layerPlayer;
	GameBaseObject * m_HeatBox;

	int m_iLives;
	int m_iCurrentPlayer;		//0 : 레이무, 1 : 마리사
	int m_iAbilityEnergy;
	bool m_bMoving;

};
#include "GamePlayer.h"
#include "GameObject.h"

GamePlayer::GamePlayer()
{

}

GamePlayer::~GamePlayer()
{
	m_Characters[CHARATYPE_REIMU]->release();
	m_Characters[CHARATYPE_MARISA]->release();
}

void GamePlayer::InitPlayer()
{
	m_Characters[CHARATYPE_REIMU] = new GameObject;
	m_Characters[CHARATYPE_REIMU]->initWithFile("player/reimu/player.png");
	m_Characters[CHARATYPE_REIMU]->AddSprAnimation("player/reimu/player.png", 94, 102, 11);
	//m_Characters[CHARATYPE_REIMU]->autorelease();

	m_Characters[CHARATYPE_MARISA] = new GameObject;
	m_Characters[CHARATYPE_MARISA]->initWithFile("player/marisa/player.png");
	m_Characters[CHARATYPE_MARISA]->AddSprAnimation("player/marisa/player.png", 55, 100, 10);
	//m_Characters[CHARATYPE_MARISA]->autorelease();

	m_iLives = 3;
	m_iCurrentPlayer = CHARATYPE_REIMU;
	m_iAbilityEnergy = 100;
	m_bCharaChange = false;

	m_bMoving = false;

}

void GamePlayer::SetPosition(int IN_fX, int IN_fY)
{
	m_fX = IN_fX;
	m_fY = IN_fY;
	m_Characters[m_iCurrentPlayer]->setPosition(IN_fX, IN_fY);

}
Vec2 GamePlayer::GetPosition()
{
	return Vec2(m_fX, m_fY);
}

bool GamePlayer::MoveTo(int IN_fDestX, int IN_fDestY)
{
	return true;		//쓰지 않음
	if (m_bMoving == false)
	{
		m_bMoving = true;
	}
	return true;
}

GameObject * GamePlayer::GetCurrentCharacter()
{
	return m_Characters[m_iCurrentPlayer];
}

int GamePlayer::ChangePlayer()
{
	if (m_iCurrentPlayer == CHARATYPE_REIMU)
	{
		m_iCurrentPlayer = CHARATYPE_MARISA;
	}
	else if (m_iCurrentPlayer == CHARATYPE_MARISA)
	{
		m_iCurrentPlayer = CHARATYPE_REIMU;
	}

	m_Characters[m_iCurrentPlayer]->setPosition(m_fX, m_fY);

	return m_iCurrentPlayer;
}
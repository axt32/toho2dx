#include "GamePlayer.h"
#include "GameObject.h"

#define REIMU_WIDTH 94
#define REIMU_HEIGHT 102
#define REIMU_FRAMES 11

#define MARISA_WIDTH 55
#define MARISA_HEIGHT 100
#define MARISA_FRAMES 10

GamePlayer::GamePlayer()
{

}

GamePlayer::~GamePlayer()
{
	m_Characters[CHARATYPE_REIMU]->release();
	m_Characters[CHARATYPE_MARISA]->release();
	m_HeatBox->release();
	m_layerPlayer->release();
}

void GamePlayer::InitPlayer()
{
	m_Characters[CHARATYPE_REIMU] = new GameObject;
	m_Characters[CHARATYPE_REIMU]->initWithFile("player/reimu/player.png");
	m_Characters[CHARATYPE_REIMU]->AddSprAnimation("player/reimu/player.png", REIMU_WIDTH, REIMU_HEIGHT, REIMU_FRAMES);

	m_Characters[CHARATYPE_MARISA] = new GameObject;
	m_Characters[CHARATYPE_MARISA]->initWithFile("player/marisa/player.png");
	m_Characters[CHARATYPE_MARISA]->AddSprAnimation("player/marisa/player.png", MARISA_WIDTH, MARISA_HEIGHT, MARISA_FRAMES);

	m_iLives = 3;
	m_iCurrentPlayer = CHARATYPE_REIMU;
	m_iAbilityEnergy = 100;

	m_bMoving = false;

	m_HeatBox = new GameObject;
	m_HeatBox->initWithFile("player/common/heatbox.png");

	m_layerPlayer = Layer::create();

	m_layerPlayer->addChild(m_Characters[CHARATYPE_REIMU], 0);
	m_layerPlayer->addChild(m_Characters[CHARATYPE_MARISA], 0);
	m_Characters[CHARATYPE_MARISA]->setVisible(false);
	m_layerPlayer->addChild(m_HeatBox);

}

void GamePlayer::SetPosition(int IN_fX, int IN_fY)
{
	m_layerPlayer->setPosition(IN_fX, IN_fY);
}
Vec2 GamePlayer::GetPosition()
{
	return Vec2(m_layerPlayer->getPositionX(), m_layerPlayer->getPositionY());
}

GameObject * GamePlayer::GetCurrentCharacter()
{
	return m_Characters[m_iCurrentPlayer];
}

GameObject * GamePlayer::GetCharacter(CHARATYPE IN_iType)
{
	return m_Characters[IN_iType];
}

int GamePlayer::ChangePlayer()
{
	if (m_iCurrentPlayer == CHARATYPE_REIMU)
	{
		m_iCurrentPlayer = CHARATYPE_MARISA;
		m_Characters[CHARATYPE_REIMU]->setVisible(false);
		m_Characters[CHARATYPE_MARISA]->setVisible(true);
	}
	else if (m_iCurrentPlayer == CHARATYPE_MARISA)
	{
		m_iCurrentPlayer = CHARATYPE_REIMU;
		m_Characters[CHARATYPE_MARISA]->setVisible(false);
		m_Characters[CHARATYPE_REIMU]->setVisible(true);
	}

	return m_iCurrentPlayer;
}
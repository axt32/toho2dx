#include "GameExplosion.h"
#include "Common.h"

GameExplosion::GameExplosion()
{
	m_bInsideCheck = false;
	m_bBoundaryCheck = false;
}

GameExplosion::~GameExplosion()
{

}

void GameExplosion::update(float dt)
{

	GameCommonObject::update(dt);
}
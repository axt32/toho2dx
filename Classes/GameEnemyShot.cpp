#include "GameEnemyShot.h"

GameEnemyShot::GameEnemyShot()
{
	m_bInsideCheck = false;
	m_bBoundaryCheck = true;
}

GameEnemyShot::~GameEnemyShot()
{
	CCLOG("Game Enemy Shot Deleted");
}
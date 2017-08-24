#include "GameEnemy.h"

GameEnemy::GameEnemy()
{
	m_bInsideCheck = true;
	m_bBoundaryCheck = true;
}

GameEnemy::~GameEnemy()
{
	CCLOG("Game Enemy Deleted");
}
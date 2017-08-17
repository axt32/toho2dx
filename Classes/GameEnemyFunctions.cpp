#include "GameEnemyFunctions.h"

using namespace EnemyFunctions;

EnemyFunction_Test::EnemyFunction_Test()
{

}

EnemyFunction_Test::~EnemyFunction_Test()
{
	CCLOG("EnemyFunction Test Destructor Invoked!");
}

void EnemyFunction_Test::InitCustomFunction()
{
	CCLOG("EnemyFunction Test Init Invoked!");
}
void EnemyFunction_Test::Run()
{
	CCLOG("EnemyFunction Test Run Invoked!");
}
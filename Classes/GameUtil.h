#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameUtil
{
public:
	static bool CircleCollisionCheck(float IN_fX1, float IN_fY1, float IN_fRadius1, float IN_fX2, float IN_fY2, float IN_fRadius2);
};
#include "GameUtil.h"

bool GameUtil::CircleCollisionCheck(float IN_fX1, float IN_fY1, float IN_fRadius1, float IN_fX2, float IN_fY2, float IN_fRadius2)
{
	if (pow(abs(IN_fX1 - IN_fX2), 2) +
		pow(abs(IN_fY1 - IN_fY2), 2)
		<= pow((IN_fRadius1 + IN_fRadius2), 2))
	{
		return true;
	}

	return false;
}
#include "objBullet.h"

objBullet::objBullet()
{
}

objBullet::~objBullet()
{
}

objBullet * objBullet::createAndInit( float rotation )
{
	objBullet * bullet = new objBullet();
	if (!bullet->initWithFile("player/reimu/shot0.png"))
	{
		int x;
		x = 1;
	}
	bullet->autorelease();
	bullet->dirX = sinf(CC_DEGREES_TO_RADIANS(rotation));
	bullet->dirY = cosf(CC_DEGREES_TO_RADIANS(rotation));
	bullet->schedule(schedule_selector(objBullet::update));
	return bullet;

}

void objBullet::update(float dt)
{
	this->setPositionX(this->getPositionX() + (dirX * 1000 * dt));
	this->setPositionY(this->getPositionY() + (dirY * 1000 * dt));
}
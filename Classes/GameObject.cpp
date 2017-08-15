#include "GameObject.h"
#include "Common.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

void GameObject::SetSpeedAngle(float IN_fSpeed, float IN_fAngle)
{
	m_fSpeed = IN_fSpeed;
	m_fAngle = IN_fAngle;
	this->schedule(schedule_selector(GameObject::update));
}

bool GameObject::AddSprAnimation(std::string IN_strFileName, int IN_iWidth, int IN_iHeight, int IN_iFrames)
{
	Vector<SpriteFrame*> animFrames;

	for (int i = 0; i < IN_iFrames; i++)
	{
		animFrames.pushBack(SpriteFrame::create(IN_strFileName, Rect(i * IN_iWidth, 0, IN_iWidth, IN_iHeight)));	//Rect¸¦ ¾²¸é ¿Þ¼Õ ÁÂÇ¥°è
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));

	return true;
}

bool GameObject::MoveTo(float IN_fDestX, float IN_fDestY, float IN_fDuration, SEL_CallFuncN IN_Function)
{
	CCFiniteTimeAction* actionMove = CCMoveTo::create((float)IN_fDuration, ccp(IN_fDestX, IN_fDestY));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, IN_Function);
	this->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

	return true;
}

void GameObject::update(float dt)
{
	float fdirX = sinf(CC_DEGREES_TO_RADIANS(m_fAngle));
	float fdirY = cosf(CC_DEGREES_TO_RADIANS(m_fAngle));
	this->setPositionX(this->getPositionX() + (fdirX * 1000 * dt));
	this->setPositionY(this->getPositionY() + (fdirY * 1000 * dt));

	//¹°Ã¼°¡ ¿Ü°ûÀ» ¹þ¾î³ª¸é Áö¿î´Ù
	cocos2d::Size size = this->getContentSize();
	if (this->getPositionX() + (size.width / 2.0f) < 0 || this->getPositionX() - (size.width / 2.0f) > GAME_WIDTH
		|| this->getPositionY() + (size.height / 2.0f) < 0 || this->getPositionY() - (size.height / 2.0f) > GAME_HEIGHT )
	{
		this->removeFromParent();
	}

}
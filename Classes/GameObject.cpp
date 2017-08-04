#include "GameObject.h"

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
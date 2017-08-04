#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;

class GameObject : public Sprite
{
private:

public:
	bool AddSprAnimation(std::string IN_strFileName, int IN_iWidth, int IN_iHeight, int IN_iFrames);
	bool MoveTo(float IN_fDestX, float IN_fDestY, float IN_fDuration, SEL_CallFuncN IN_Function);
};
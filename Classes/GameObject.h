#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;

class GameObject : public Sprite
{
private:

public:
	bool m_bAutoMove;
	bool m_bAutoRotation;
	bool m_bBoundaryCheck;

	float m_fSpeed;
	float m_fAngle;
	float m_fAutoRotationAngle;

	GameObject();
	~GameObject();

	void SetSpeedAngle(float IN_fSpeed, float IN_fAngle);
	void SetAutoRotation(bool IN_bAutoRotation = true, float IN_fAutoRotationAngle = 1.0f);
	
	bool AddSprAnimation(std::string IN_strFileName, int IN_iWidth, int IN_iHeight, int IN_iFrames);
	bool MoveTo(float IN_fDestX, float IN_fDestY, float IN_fDuration, SEL_CallFuncN IN_Function);

	void update(float dt);
};
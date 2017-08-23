#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;

class GameBaseObject : public Sprite
{
private:
	bool m_bInsideOK;

public:
	GameBaseObject();
	virtual ~GameBaseObject();

	bool m_bAutoMove;
	bool m_bAutoRotation	;//자동회전 (기능 불완전. 윈도우에서는 잘 되는데 안드로이드에서는 튕김)
	bool m_bInsideCheck;
	bool m_bBoundaryCheck;		

	float m_fSpeed;
	float m_fAngle;
	float m_fAutoRotationAngle;

	float m_fCollisionRadius;		//충돌체크 판정 범위

	void SetSpeedAngle(float IN_fSpeed, float IN_fAngle);		//AngleSpeed로 할지, SpeedAngle로 할지 어느 한쪽으로 통일시켜야됨.
	void SetAutoRotation(bool IN_bAutoRotation = true, float IN_fAutoRotationAngle = 1.0f);
	
	bool AddSprAnimation(std::string IN_strFileName, int IN_iWidth, int IN_iHeight, int IN_iFrames);
	bool MoveTo(float IN_fDestX, float IN_fDestY, float IN_fDuration, SEL_CallFuncN IN_Function);

	virtual void update(float dt);
};
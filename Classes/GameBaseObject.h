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
	bool m_bAutoRotation	;//�ڵ�ȸ�� (��� �ҿ���. �����쿡���� �� �Ǵµ� �ȵ���̵忡���� ƨ��)
	bool m_bInsideCheck;
	bool m_bBoundaryCheck;		

	float m_fSpeed;
	float m_fAngle;
	float m_fAutoRotationAngle;

	float m_fCollisionRadius;		//�浹üũ ���� ����

	void SetSpeedAngle(float IN_fSpeed, float IN_fAngle);		//AngleSpeed�� ����, SpeedAngle�� ���� ��� �������� ���Ͻ��Ѿߵ�.
	void SetAutoRotation(bool IN_bAutoRotation = true, float IN_fAutoRotationAngle = 1.0f);
	
	bool AddSprAnimation(std::string IN_strFileName, int IN_iWidth, int IN_iHeight, int IN_iFrames);
	bool MoveTo(float IN_fDestX, float IN_fDestY, float IN_fDuration, SEL_CallFuncN IN_Function);

	virtual void update(float dt);
};
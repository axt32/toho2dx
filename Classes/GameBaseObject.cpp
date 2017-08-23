#include "GameBaseObject.h"
#include "Common.h"

GameBaseObject::GameBaseObject()
{
	m_bInsideOK = false;

	m_bAutoMove = false;
	m_bAutoRotation = false;
	m_bInsideCheck = false;
	m_bBoundaryCheck = false;
	m_fAutoRotationAngle = 1.0f;
	this->schedule(schedule_selector(GameBaseObject::update));
}

GameBaseObject::~GameBaseObject()
{

}

void GameBaseObject::SetSpeedAngle(float IN_fSpeed, float IN_fAngle)
{
	m_fSpeed = IN_fSpeed;
	m_fAngle = IN_fAngle;
	m_bAutoMove = true;
}

void GameBaseObject::SetAutoRotation(bool IN_bAutoRotation, float IN_fAutoRotationAngle)
{
	m_fAutoRotationAngle = IN_fAutoRotationAngle;
	m_bAutoRotation = IN_bAutoRotation;
}

bool GameBaseObject::AddSprAnimation(std::string IN_strFileName, int IN_iWidth, int IN_iHeight, int IN_iFrames)
{
	Vector<SpriteFrame*> animFrames;

	for (int i = 0; i < IN_iFrames; i++)
	{
		animFrames.pushBack(SpriteFrame::create(IN_strFileName, Rect(i * IN_iWidth, 0, IN_iWidth, IN_iHeight)));	//Rect를 쓰면 왼손 좌표계
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));

	return true;
}

bool GameBaseObject::MoveTo(float IN_fDestX, float IN_fDestY, float IN_fDuration, SEL_CallFuncN IN_Function)
{
	CCFiniteTimeAction* actionMove = CCMoveTo::create((float)IN_fDuration, ccp(IN_fDestX, IN_fDestY));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, IN_Function);
	this->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

	return true;
}

void GameBaseObject::update(float dt)
{
	//이동
	if ( m_bAutoMove == true )
	{
		float fdirX = sinf(CC_DEGREES_TO_RADIANS(m_fAngle));
		float fdirY = cosf(CC_DEGREES_TO_RADIANS(m_fAngle));
		this->setPositionX(this->getPositionX() + (fdirX * m_fSpeed));		//dt를 곱해야될것같은 부분인데, 일단 패스
		this->setPositionY(this->getPositionY() + (fdirY * m_fSpeed));
	}

	cocos2d::Size size = this->getContentSize();

	auto BoundaryCheck = [&] ()
	{
		if (m_bBoundaryCheck == true)
		{
			if (this->getPositionX() + (size.width / 2.0f) < 0 || this->getPositionX() - (size.width / 2.0f) > GAME_WIDTH
				|| this->getPositionY() + (size.height / 2.0f) < 0 || this->getPositionY() - (size.height / 2.0f) > GAME_HEIGHT)
			{
				this->removeFromParent();
			}
		}
	};

	//인사이드 & 바운더리 체크
	if (m_bInsideCheck == true)
	{
		if (m_bInsideOK == false)
		{
			if (this->getPositionX() + (size.width / 2.f) >= 0)
				if (this->getPositionX() - (size.width / 2.f) <= GAME_WIDTH)
					if (this->getPositionY() + (size.height / 2.f) >= 0)
						if (this->getPositionY() - (size.height / 2.f) <= GAME_HEIGHT)
						{
							m_bInsideOK = true;
						}
		}
		else
		{
			BoundaryCheck();
		}
	}
	else
	{
		BoundaryCheck();
	}

	//자동회전 (기능 불완전. 윈도우에서는 잘 되는데 안드로이드에서는 튕김)
	if (m_bAutoRotation == true)
	{
		float fRotation = this->getRotation() + m_fAutoRotationAngle;
		if (fRotation >= 360.0f)
		{
			fRotation -= 360.0f;
		}
		else if (fRotation < 0.0f)
		{
			fRotation += 360.0f;

		}

		this->setRotation(fRotation);
	}
}
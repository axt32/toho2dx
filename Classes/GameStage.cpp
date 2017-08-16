#include "GameStage.h"
#include "SimpleAudioEngine.h"
#include "GameUtil.h"

USING_NS_CC;

Scene* GameStage::createScene()
{
	return GameStage::create();
}

// on "init" you need to initialize your instance
bool GameStage::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto btnChange = MenuItemImage::create(
		"ui/btn_change.png",
		"ui/btn_change.png",
		CC_CALLBACK_1(GameStage::menuChangeCallback, this));

	btnChange->setPosition(Vec2(origin.x + visibleSize.width - btnChange->getContentSize().width * 2,
		origin.y + btnChange->getContentSize().height / 2));

	auto btnBomber = MenuItemImage::create(
		"ui/btn_bomber.png",
		"ui/btn_bomber.png",
		CC_CALLBACK_1(GameStage::menuBomberCallback, this));

	btnBomber->setPosition(Vec2(origin.x + visibleSize.width - btnChange->getContentSize().width / 2,
		origin.y + btnBomber->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menuChange = Menu::create(btnChange, NULL);
	menuChange->setPosition(Vec2::ZERO);
	this->addChild(menuChange, 1);

	auto menuBomber = Menu::create(btnBomber, NULL);
	menuBomber->setPosition(Vec2::ZERO);
	this->addChild(menuBomber, 1);

	//�������� ��� �ʱ�ȭ
	m_sprBackground = Sprite::create("stage1/back.png");
	m_sprBackground->setPosition(320, 180);		//���� ���ó�� �ʿ�
	this->addChild(m_sprBackground);

	//�÷��̾� �ʱ�ȭ
	m_Player.InitPlayer();
	this->addChild(m_Player.m_layerPlayer);

	m_Player.SetPosition(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y);

	//��ġ �̺�Ʈ (�÷��̾� �̵� ����)
	EventDispatcher * dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameStage::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameStage::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameStage::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//�÷��̾� �Ѿ� �ڵ� �߻� �׼�
	CallFunc * action_0 = CallFunc::create(CC_CALLBACK_0(GameStage::PlayerFireBullet, this));
	CCDelayTime * action_1 = CCDelayTime::create(0.1f);
	Sequence * action_playerfirebullet = Sequence::create(action_0, action_1, NULL);
	CCRepeatForever * action_repeat = CCRepeatForever::create(action_playerfirebullet);
	m_Player.m_layerPlayer->runAction(action_repeat);

	//�Ѿ� ���̾� (autorelease �ϸ� ���α׷��� ����)
	layerBulletEnemy = Layer::create();
	layerBulletEnemy->setAnchorPoint(ccp(0, 0));
	layerBulletEnemy->setPosition(ccp(0, 0));
	this->addChild(layerBulletEnemy);

	//���������� ������ ��������
	this->scheduleUpdate();

	return true;
}

void GameStage::MovePlayer(float IN_fDestX, float IN_fDestY)
{
	m_Player.m_layerPlayer->setPosition(IN_fDestX, IN_fDestY);

	//���� ����.
//	CCFiniteTimeAction* actionMove = CCMoveTo::create((float)0.1f, ccp(IN_fDestX, IN_fDestY));
//	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameStage::spriteMoveFinished));
//	m_Player.m_layerPlayer->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void GameStage::FireBullet()
{
	//ĳ���ͺ���, ���⺰�� �߻� �޼ҵ带 �ٸ��� �ؾ� �Ѵ�. �ϴ��� ���̹� ���� ����

	GameObject * pBullet = new GameObject;	
	pBullet->initWithFile("player/reimu/shot0.png");
	Vec2 pos = m_Player.GetPosition();
	pBullet->setPosition(Point(pos.x, pos.y));
	pBullet->SetSpeedAngle(3.0f, 90.0f);
	pBullet->setRotation(90.0f);
	pBullet->autorelease();
	layerBulletEnemy->addChild(pBullet);
}

void GameStage::PlayerFireBullet() {

	//CCLOG("goCall %s", (char*)d);
	//Sprite *spr = (Sprite *)pSender;

	if (m_Player.m_iCurrentPlayer == CHARATYPE_REIMU)
	{
		auto MakeReimuShot = [&] (float IN_fY)
		{
			GameObject * pBullet = new GameObject;
			pBullet->initWithFile("player/reimu/shot0.png");
			Vec2 pos = m_Player.GetPosition();
			pBullet->setPosition(Point(pos.x, pos.y + IN_fY));
			pBullet->SetSpeedAngle(2.0f, 90.0f);
			pBullet->setRotation(90.0f);
			pBullet->m_bBoundaryCheck = true;
			pBullet->autorelease();
			layerBulletEnemy->addChild(pBullet);
		};

		MakeReimuShot(20.0f);
		MakeReimuShot(0.f);
		MakeReimuShot(-20.0f);

	}
	else if (m_Player.m_iCurrentPlayer == CHARATYPE_MARISA)
	{

		auto MakeMarisaShot = [&] (float IN_fY, float IN_fAngle)
		{
			GameObject * pBullet = new GameObject;
			pBullet->initWithSpriteFrame(SpriteFrame::create("player/marisa/shot0.png", Rect(RandomHelper::random_int(0, 7) * 30, 0, 30, 28)));
			Vec2 pos = m_Player.GetPosition();
			pBullet->setPosition(Point(pos.x, pos.y + IN_fY));
			float fShotAngle = 90.f + IN_fAngle;
			pBullet->SetSpeedAngle(2.0f, fShotAngle);
			pBullet->setRotation(fShotAngle);		//
			//pBullet->SetAutoRotation();
			pBullet->m_bBoundaryCheck = true;
			pBullet->autorelease();
			layerBulletEnemy->addChild(pBullet);
		};


		MakeMarisaShot(20.0f, -5.0f);
		MakeMarisaShot(0.f, 0.f);
		MakeMarisaShot(-20.0f, 5.0f);

	}

}

bool GameStage::onTouchBegan(Touch * touch, Event * event)
{
	//������ġ ����ȵ�?
	auto target = event->getCurrentTarget();
	touchPoint = target->convertToNodeSpace(touch->getLocation());

	if (m_Player.m_bMoving == false)
	{
		if (GameUtil::CircleCollisionCheck(m_Player.GetPosition().x, m_Player.GetPosition().y, PLAYERSIZE_RADIUS, touchPoint.x, touchPoint.y, 1.0f) == true)
		{
			m_Player.m_bMoving = true;
			MovePlayer(touchPoint.x, touchPoint.y);
		}
	}

	return true;
}

void GameStage::onTouchMoved(Touch * touch, Event * event)
{
	if (m_Player.m_bMoving == true)
	{
		auto target = event->getCurrentTarget();
		touchPoint = target->convertToNodeSpace(touch->getLocation());
		MovePlayer(touchPoint.x, touchPoint.y);
	}

	//FireBullet();	//�׽�Ʈ��
}

void GameStage::onTouchEnded(Touch * touch, Event * event)
{
	m_Player.m_bMoving = false;
}

void GameStage::update(float dt)
{

}

void GameStage::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}

void GameStage::menuChangeCallback(cocos2d::Ref* pSender)
{
	m_Player.ChangePlayer();
}

void GameStage::menuBomberCallback(cocos2d::Ref* pSender)
{
	
}

void GameStage::spriteMoveFinished(CCNode* sender)
{

}
#include "GameStage.h"
#include "SimpleAudioEngine.h"
#include "objBullet.h"

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

	//스테이지 배경 초기화
	m_sprWallpaper = Sprite::create("stage1/back.png");
	m_sprWallpaper->setPosition(320, 180);		//추후 상수처리 필요
	this->addChild(m_sprWallpaper);

	//플레이어 레이어
	layerPlayer = Layer::create();
	layerPlayer->setAnchorPoint(ccp(0, 0));
	layerPlayer->setPosition(ccp(0, 0));
	this->addChild(layerPlayer);

	//플레이어 초기화
	m_Player.InitPlayer();
	m_Player.SetPosition(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y);
	layerPlayer->addChild(m_Player.GetCurrentCharacter(), 0);

	//총알 레이어
	layerBullet = Layer::create();
	layerBullet->setAnchorPoint(ccp(0, 0));
	layerBullet->setPosition(ccp(0, 0));
	this->addChild(layerBullet);

	EventDispatcher * dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameStage::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameStage::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameStage::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}

void GameStage::MovePlayer(float IN_fDestX, float IN_fDestY)
{
	if (m_Player.m_bMoving == false)
	{
		m_Player.SetPosition(IN_fDestX, IN_fDestY);
		CCFiniteTimeAction* actionMove = CCMoveTo::create((float)0.1f, ccp(IN_fDestX, IN_fDestY));
		CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameStage::spriteMoveFinished));
		m_Player.GetCurrentCharacter()->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
		m_Player.m_bMoving = true;
	}
}

void GameStage::FireBullet()
{
	//총알을 레이무의 자식으로 설정
//	objBullet * bullet = objBullet::createAndInit(m_sprReimu->getRotation());
	objBullet * bullet = objBullet::createAndInit(90.0f);
	Vec2 pos = m_Player.GetPosition();
	bullet->setPosition(Point(pos.x, pos.y));
//	bullet->setRotation(m_sprReimu->getRotation());
	bullet->setRotation(90.0f);
	layerBullet->addChild(bullet);
}

bool GameStage::onTouchBegan(Touch * touch, Event * event)
{
	auto target = event->getCurrentTarget();
	touchPoint = target->convertToNodeSpace(touch->getLocation());

	MovePlayer(touchPoint.x, touchPoint.y);

	return true;
}

void GameStage::onTouchMoved(Touch * touch, Event * event)
{
	auto target = event->getCurrentTarget();
	touchPoint = target->convertToNodeSpace(touch->getLocation());

	MovePlayer(touchPoint.x, touchPoint.y);
}

void GameStage::onTouchEnded(Touch * touch, Event * event)
{

}

void GameStage::update(float dt)
{
	//상시 총알 발사
	//FireBullet();
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
	layerPlayer->removeChild(m_Player.GetCurrentCharacter());
	m_Player.ChangePlayer();
	layerPlayer->addChild(m_Player.GetCurrentCharacter(), 0);
}

void GameStage::menuBomberCallback(cocos2d::Ref* pSender)
{


}

void GameStage::spriteMoveFinished(CCNode* sender)
{
	m_Player.m_bMoving = false;
}
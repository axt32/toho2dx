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
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameStage::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	m_sprReimu = Sprite::create("player/reimu/player.png");

	m_sprWallpaper = Sprite::create("stage1/back.png");

	m_sprWallpaper->setPosition(320, 180);		//추후 상수처리 필요
	this->addChild(m_sprWallpaper);

	Vector<SpriteFrame*> animFrames;
	for (int i = 0; i < 11; i++)
	{
		animFrames.pushBack(SpriteFrame::create("player/reimu/player.png", Rect(i * 94, 0, 94, 102)));	//Rect를 쓰면 왼손 좌표계
	}

	m_sprReimu->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = Animate::create(animation);
	m_sprReimu->runAction(RepeatForever::create(animate));

	this->addChild(m_sprReimu, 0);

	layerBullet = Layer::create();
	layerBullet->setAnchorPoint(ccp(0, 0));
	layerBullet->setPosition(ccp(0, 0));
	this->addChild(layerBullet);

	//CCFiniteTimeAction* actionMove = CCMoveTo::create((float)10.0,ccp(0 - m_sprReimu->getPositionX(), 200.0f));
	//CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::spriteMoveFinished));
	//m_sprReimu->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

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

void GameStage::RotateReimu(float ct)
{

	if (m_sprReimu->getRotation() > angleOffset)
	{
		m_sprReimu->setRotation(m_sprReimu->getRotation() - 2.0f);
	}
	else if (m_sprReimu->getRotation() < angleOffset)
	{
		m_sprReimu->setRotation(m_sprReimu->getRotation() + 2.0f);
	}

}

void GameStage::FireBullet()
{
	//총알을 레이무의 자식으로 설정
	objBullet * bullet = objBullet::createAndInit(m_sprReimu->getRotation());
	Vec2 pos = m_sprReimu->getPosition();
	bullet->setPosition(Point(pos.x, pos.y));
	bullet->setRotation(m_sprReimu->getRotation());
	layerBullet->addChild(bullet);
}

bool GameStage::onTouchBegan(Touch * touch, Event * event)
{
	auto target = event->getCurrentTarget();
	touchPoint = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 100, s.width, s.height);
	//if (rect.containsPoint(touchPoint));		//일단은 렉트 체크는 하지 않는다.
	{
		//터치 각도 구하기
		float diffX = touchPoint.x - s.width / 2.0f;
		float diffY = touchPoint.y - s.height / 2.0f;
		float angleRadian = atan2f(diffY, diffX);
		angleOffset = CC_RADIANS_TO_DEGREES(angleRadian) * (-1.0f) + 90.0f;
		this->schedule(schedule_selector(GameStage::RotateReimu));
		FireBullet();
		return true;
	}

	return false;
}

void GameStage::onTouchMoved(Touch * touch, Event * event)
{
	auto target = event->getCurrentTarget();
	touchPoint = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 100, s.width, s.height);
	//터치 각도 구하기
	float diffX = touchPoint.x - s.width / 2.0f;
	float diffY = touchPoint.y - s.height / 2.0f;
	float angleRadian = atan2f(diffY, diffX);
	angleOffset = CC_RADIANS_TO_DEGREES(angleRadian) * (-1.0f) + 90.0f;
	FireBullet();
}
void GameStage::onTouchEnded(Touch * touch, Event * event)
{
	this->unschedule(schedule_selector(GameStage::RotateReimu));
}

void GameStage::update(float dt)
{

}

void GameStage::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
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

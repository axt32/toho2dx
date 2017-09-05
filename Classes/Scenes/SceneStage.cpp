#include "SceneStage.h"
#include "SimpleAudioEngine.h"
#include "GameUtil.h"
#include "GameObjects/GamePlayerShot.h"
#include "GameObjects/GameEnemy.h"
#include "GameObjects/GameEnemyShot.h"
#include "GameObjects/GameExplosion.h"
#include "CustomFunctions/GameEnemyFunctions.h"
#include "Common.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SceneStage::createScene()
{
	return SceneStage::create();
}

// on "init" you need to initialize your instance
bool SceneStage::init()
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
		CC_CALLBACK_1(SceneStage::menuChangeCallback, this));

	btnChange->setPosition(Vec2(origin.x + visibleSize.width - btnChange->getContentSize().width * 2,
		origin.y + btnChange->getContentSize().height / 2));

	auto btnBomber = MenuItemImage::create(
		"ui/btn_bomber.png",
		"ui/btn_bomber.png",
		CC_CALLBACK_1(SceneStage::menuBomberCallback, this));

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
	m_sprBackground = Sprite::create("stage1/back.png");
	m_sprBackground->setPosition(320, 180);		//추후 상수처리 필요
	this->addChild(m_sprBackground);

	//플레이어 초기화
	m_Player.InitPlayer();
	this->addChild(m_Player.m_layerPlayer);

	m_Player.SetPosition(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y);

	//터치 이벤트 (플레이어 이동 관련)
	EventDispatcher * dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SceneStage::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SceneStage::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneStage::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//플레이어 총알 자동 발사 액션
	CallFunc * action_0 = CallFunc::create(CC_CALLBACK_0(SceneStage::PlayerFireBullet, this));
	CCDelayTime * action_1 = CCDelayTime::create(0.25f);
	Sequence * action_playerfirebullet = Sequence::create(action_0, action_1, NULL);
	CCRepeatForever * action_repeat = CCRepeatForever::create(action_playerfirebullet);
	m_Player.m_layerPlayer->runAction(action_repeat);

	//레이어 (autorelease 하면 프로그램이 꼬임)
	m_pLayerPlayerShot = Layer::create();
	m_pLayerPlayerShot = Layer::create();
	m_pLayerPlayerShot->setAnchorPoint(ccp(0, 0));
	m_pLayerPlayerShot->setPosition(ccp(0, 0));
	this->addChild(m_pLayerPlayerShot);

	m_pLayerEnemy = Layer::create();
	m_pLayerEnemy->setAnchorPoint(ccp(0, 0));
	m_pLayerEnemy->setPosition(ccp(0, 0));
	this->addChild(m_pLayerEnemy);

	m_pLayerEnemyShot = Layer::create();
	m_pLayerEnemyShot->setAnchorPoint(ccp(0, 0));
	m_pLayerEnemyShot->setPosition(ccp(0, 0));
	this->addChild(m_pLayerEnemyShot);

	m_pLayerExplosion = Layer::create();
	m_pLayerExplosion->setAnchorPoint(ccp(0, 0));
	m_pLayerExplosion->setPosition(ccp(0, 0));
	this->addChild(m_pLayerExplosion);

	//변수 초기화
	m_iCurrentFrame = 0;

	//스테이지의 스케줄 업데이터
	this->scheduleUpdate();

	//음악 재생
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.f);
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.35f);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm/stage1.mp3", true);

	return true;
}

void SceneStage::MovePlayer(float IN_fDestX, float IN_fDestY)
{
	m_Player.m_layerPlayer->setPosition(IN_fDestX, IN_fDestY);

	//쓰지 않음.
//	CCFiniteTimeAction* actionMove = CCMoveTo::create((float)0.1f, ccp(IN_fDestX, IN_fDestY));
//	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this, callfuncN_selector(GameStage::spriteMoveFinished));
//	m_Player.m_layerPlayer->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void SceneStage::PlayerFireBullet() {

	//CCLOG("goCall %s", (char*)d);
	//Sprite *spr = (Sprite *)pSender;

	if (m_Player.m_iCurrentPlayer == CHARATYPE_REIMU)
	{
		auto MakeReimuShot = [&] (float IN_fY)
		{
			GamePlayerShot * pBullet = new GamePlayerShot;
			pBullet->initWithFile("player/reimu/shot0.png");
			Vec2 pos = m_Player.GetPosition();
			pBullet->setPosition(Point(pos.x, pos.y + IN_fY));
			pBullet->SetSpeedAngle(10.0f, 90.0f);
			pBullet->setRotation(90.0f);
			pBullet->m_fCollisionRadius = 8.f;
			pBullet->m_iDamage = 3;
			m_pLayerPlayerShot->addChild(pBullet);
			pBullet->autorelease();
		};

		MakeReimuShot(22.0f);
		MakeReimuShot(0.f);
		MakeReimuShot(-22.0f);

	}
	else if (m_Player.m_iCurrentPlayer == CHARATYPE_MARISA)
	{

		auto MakeMarisaShot = [&](float IN_fY, float IN_fAngle)
		{
			GamePlayerShot * pBullet = new GamePlayerShot;
			pBullet->initWithSpriteFrame(SpriteFrame::create("player/marisa/shot0.png", Rect(RandomHelper::random_int(0, 7) * 30, 0, MARISA_SHOT_WIDTH, MARISA_SHOT_HEIGHT)));
			Vec2 pos = m_Player.GetPosition();
			pBullet->setPosition(Point(pos.x, pos.y + IN_fY));
			float fShotAngle = 90.f + IN_fAngle;
			pBullet->SetSpeedAngle(10.f, fShotAngle);
			pBullet->setRotation(fShotAngle);		//
			//pBullet->SetAutoRotation();
			pBullet->m_fCollisionRadius = 14.f;
			pBullet->m_iDamage = 3;
			m_pLayerPlayerShot->addChild(pBullet);
			pBullet->autorelease();
		};


		MakeMarisaShot(20.0f, -5.0f);
		MakeMarisaShot(0.f, 0.f);
		MakeMarisaShot(-20.0f, 5.0f);

	}

	SimpleAudioEngine::getInstance()->playEffect("se/playershot.wav", false);

}

void SceneStage::MakeEnemy()
{
	//에너미 생성
	GameEnemy * pEnemy = new GameEnemy;
	pEnemy->initWithFile("enemies/type1.png");
	pEnemy->AddSprAnimation("enemies/type1.png", ENEMY_TYPE1_WIDTH, ENEMY_TYPE1_HEIGHT, ENEMY_TYPE1_FRAMES);
	pEnemy->setPosition(Point(100.f, 100.f));
	pEnemy->m_fCollisionRadius = 15.f;
	pEnemy->m_iHP = 9;
	pEnemy->autorelease();

	//에너미 함수 연결
	pEnemy->m_pCustomFunction = new EnemyFunctions::Stage1_EnemyPattern1;
	pEnemy->m_pCustomFunction->m_pObject = pEnemy;
	((EnemyFunctions::Stage1_EnemyPattern1 *)(pEnemy->m_pCustomFunction))->m_iMinimumDuration = 40;
	((EnemyFunctions::Stage1_EnemyPattern1 *)(pEnemy->m_pCustomFunction))->m_iMaximumDuration = 60;
	((EnemyFunctions::Stage1_EnemyPattern1 *)(pEnemy->m_pCustomFunction))->m_iBulletQuantity = 3;
	((EnemyFunctions::Stage1_EnemyPattern1 *)(pEnemy->m_pCustomFunction))->m_iBulletStyle = 1;
	((EnemyFunctions::Stage1_EnemyPattern1 *)(pEnemy->m_pCustomFunction))->m_iBulletSubStyle = RandomHelper::random_int(1, BULLET_TYPE1_STYLES) - 1;
	((EnemyFunctions::Stage1_EnemyPattern1 *)(pEnemy->m_pCustomFunction))->m_iShotBulletDestFrame = 60;
	pEnemy->InvokeInit();
	m_pLayerEnemy->addChild(pEnemy);

}

//AddAngle, AddSpeed는 인터페이스만 만들었고 기능구현은 아직 하지 않았다.
void SceneStage::MakeEnemyShot(int IN_iBulletType, int IN_iBulletSubStyle, float IN_fX, float IN_fY, float IN_fSpeed, float IN_fAddSpeed, float IN_fAngle, float IN_fAddAngle, GameCustomFunction * IN_pBarrageFunction)
{
	//총알 생성
	GameEnemyShot * pBullet = new GameEnemyShot;

	switch (IN_iBulletType)
	{
	case 1:
		pBullet->initWithFile("bullets/type1.png", Rect(IN_iBulletSubStyle * BULLET_TYPE1_WIDTH, 0, BULLET_TYPE1_WIDTH, BULLET_TYPE1_HEIGHT));
		pBullet->m_fCollisionRadius = 3.f;
		break;
	default:
		break;
	}

	pBullet->setPosition(Point(IN_fX, IN_fY));
	pBullet->SetSpeedAngle(IN_fSpeed, IN_fAngle);
	//pBullet->setRotation(IN_fAngle);
	pBullet->autorelease();

	//탄막 함수 연결
	if (IN_pBarrageFunction != nullptr)
	{
		pBullet->m_pCustomFunction = IN_pBarrageFunction;
		pBullet->m_pCustomFunction->m_pObject = pBullet;
		pBullet->InvokeInit();
	}

	m_pLayerEnemyShot->addChild(pBullet);

	SimpleAudioEngine::getInstance()->playEffect("se/enemyshot.wav", false);
}

void SceneStage::MakeExplosion(float IN_fX, float IN_fY, bool IN_bSmallExplosion)
{
	//에너미 생성
	GameExplosion * pExplosion = new GameExplosion;

	if (IN_bSmallExplosion == true)
	{
		pExplosion->init();
		pExplosion->AddSprAnimation("explosion/explosion_small.png", EXPLOSION_SMALL_WIDTH, EXPLOSION_SMALL_HEIGHT, EXPLOSION_SMALL_FRAMES, true);
	}
	else
	{
		pExplosion->init();
		pExplosion->AddSprAnimation("explosion/explosion_big.png", EXPLOSION_BIG_WIDTH, EXPLOSION_BIG_HEIGHT, EXPLOSION_BIG_FRAMES, true);
	}

	pExplosion->setPosition(Point(IN_fX, IN_fY));
	pExplosion->autorelease();
	m_pLayerExplosion->addChild(pExplosion);
}

bool SceneStage::onTouchBegan(Touch * touch, Event * event)
{
	//다중터치 고려안됨?
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

void SceneStage::onTouchMoved(Touch * touch, Event * event)
{
	if (m_Player.m_bMoving == true)
	{
		auto target = event->getCurrentTarget();
		touchPoint = target->convertToNodeSpace(touch->getLocation());
		MovePlayer(touchPoint.x, touchPoint.y);
	}
}

void SceneStage::onTouchEnded(Touch * touch, Event * event)
{
	m_Player.m_bMoving = false;
}

void SceneStage::update(float dt)
{
	if ( ++m_iCurrentFrame % 60 == 0)
	{
		for (int i = 0; i < 3; i++)
		MakeEnemy();
	}
}

void SceneStage::menuCloseCallback(Ref* pSender)
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

void SceneStage::menuChangeCallback(cocos2d::Ref* pSender)
{
	//캐릭터 체인지
	m_Player.ChangePlayer();
}

void SceneStage::menuBomberCallback(cocos2d::Ref* pSender)
{
	
}

//void GameStage::spriteMoveFinished(CCNode* sender)
//{
//
//}
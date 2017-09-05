#include "SceneLogo.h"
#include "SimpleAudioEngine.h"
#include "Common.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* SceneLogo::createScene()
{
	return SceneLogo::create();
}

// on "init" you need to initialize your instance
bool SceneLogo::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���θ޴� �׸���
	m_sprGameLogo = Sprite::create("ui/mainlogo.png");
	m_sprGameLogo->setPosition(visibleSize.width / 2.0f + origin.x, visibleSize.height / 2.0f + origin.y);
	
	this->addChild(m_sprGameLogo);

	//��ġ �̺�Ʈ �߰�
	EventDispatcher * dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SceneLogo::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SceneLogo::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneLogo::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//���������� ������ ��������
	this->scheduleUpdate();
	return true;
}

void SceneLogo::update(float dt)
{
	
}

bool SceneLogo::onTouchBegan(Touch * touch, Event * event)
{
	
	return true;
}

void SceneLogo::onTouchMoved(Touch * touch, Event * event)
{

}

void SceneLogo::onTouchEnded(Touch * touch, Event * event)
{
	g_pSceneStage = SceneStage::create();
//	Director::getInstance()->replaceScene(TransitionCrossFade::create(3.0, g_pSceneStage));		//Scene�� replace �Ǹ� autorelease �Ǵ��� ������.
	Director::getInstance()->replaceScene(g_pSceneStage);		//SceneGameStage���� init ����� ���� ������ �ɱ�?
	Director::getInstance()->purgeCachedData();
}
#include "AppDelegate.h"
#include "GameStage.h"
#include "Common.h"

USING_NS_CC;
#define TARGET_WIDTH GAME_WIDTH		//Galaxy S7 Edge -> 1920*1080
#define TARGET_HEIGHT	GAME_HEIGHT

static cocos2d::Size designResolutionSize = cocos2d::Size(TARGET_WIDTH, TARGET_HEIGHT);


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Toho2DX", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Toho2DX");
#endif
        director->setOpenGLView(glview);
    }

  #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto frameSize = glview->getFrameSize();
	CCLOG("Frame Width:%f, Height:%f", frameSize.width, frameSize.height);
	glview->setFrameSize(TARGET_WIDTH, TARGET_HEIGHT);
	glview->setFrameZoomFactor(1.0f);
  #endif

	CCSize curSize = CCSize(TARGET_WIDTH, TARGET_HEIGHT);
	glview->setDesignResolutionSize(curSize.width,
		curSize.height,
		kResolutionShowAll);
	
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0f / 60);

	register_all_packages();

	g_pGameStage = GameStage::create();
	director->runWithScene(g_pGameStage);
	CCLOG("Scene Changes");

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

#include "HelloWorldScene.h"
#include "WaveNode.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
	: m_pWaveNode(nullptr)
{
}

HelloWorld::~HelloWorld()
{
	CC_SAFE_RELEASE(m_pWaveNode);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
   
    return true;
}

void HelloWorld::onEnter()
{
	createWave();

	scheduleUpdate();

	Layer::onEnter();
}

void HelloWorld::onExit()
{
	unscheduleUpdate();

	Layer::onExit();
}

void HelloWorld::update(float delta)
{
	m_pWaveNode->update(delta);
}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	mCustomCommand.init(0);
	mCustomCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&mCustomCommand);
}

void HelloWorld::onDraw(const Mat4& transform, uint32_t flags)
{
	m_pWaveNode->onDraw(transform, flags);
}

void HelloWorld::createWave()
{
	m_pWaveNode = new WaveNode();
	m_pWaveNode->init();

	addChild(m_pWaveNode, 2);
}
	
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

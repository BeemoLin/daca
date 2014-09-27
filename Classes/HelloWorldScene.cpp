#include "HelloWorldScene.h"

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
	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);

	auto imageItem = MenuItemImage::create(
			"001.png",
			"002.png",
			CC_CALLBACK_1(HelloWorld::plugCallback, this));

	imageItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	eqItem = MenuItemImage::create("eq.png", "eq.png", CC_CALLBACK_1(HelloWorld::eqCallback, this));
	eqItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - eqItem->getContentSize().height));
	eqItem->setTag(tagEqItem);

	auto plugItem = MenuItemImage::create(
			"plug.png",
			"plug.png",
			CC_CALLBACK_1(HelloWorld::plugCallback, this));
	plugItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + plugItem->getContentSize().height));


	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, imageItem, eqItem, plugItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = LabelTTF::create("分數", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	//label->setPosition(Vec2(label->getContentSize().width,
	//                        origin.y + visibleSize.height - label->getContentSize().height));
	// add the label as a child to this layer
	//this->addChild(label, 1);

	score = 0;
	CCString* ns=CCString::createWithFormat("%d",score);
	string score_s=ns->_string;

	auto labelCoin = CCLabelAtlas::create("0", "nums_font.png", 14, 24, '0');
	this->addChild(labelCoin, 1, tagLabelCoin);
	labelCoin->setString(score_s);
	labelCoin->setScale(1);
	labelCoin->setPosition(Vec2(origin.x + 100,
				origin.y + visibleSize.height - labelCoin->getContentSize().height * 2));



	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("coin.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(sprite->getContentSize().width / 2,
				origin.y + visibleSize.height - sprite->getContentSize().height / 2));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	//this->scheduleOnce(schedule_selector(HelloWorld::update), 1.0f);
	scheduleUpdate();

	this->schedule(schedule_selector(HelloWorld::updateData), 0.5f);

	return true;
}

void HelloWorld::update(float dt)
{
	CCString* ns=CCString::createWithFormat("%d", score);
	string score_s=ns->_string;
	auto coin = (CCLabelAtlas*) this->getChildByTag(tagLabelCoin);
	coin->setString(score_s);
}

void HelloWorld::updateData(float dt)
{
	score++;
}

void HelloWorld::eqCallback(cocos2d::Ref* pSender)
{
	if(eq<2)
	{
		eq++;
	}
	else
	{
		eq = 0;
	}

	switch(eq)
	{
		case 0:
			eqItem->setNormalImage(Sprite::create("eq.png"));
			eqItem->setSelectedImage(Sprite::create("eq.png"));
			break;

		case 1:
			eqItem->setNormalImage(Sprite::create("eq2.png"));
			eqItem->setSelectedImage(Sprite::create("eq2.png"));
			break;

		case 2:
			eqItem->setNormalImage(Sprite::create("eq3.png"));
			eqItem->setSelectedImage(Sprite::create("eq3.png"));
			break;

		default:
			eqItem->setNormalImage(Sprite::create("eq.png"));
			eqItem->setSelectedImage(Sprite::create("eq.png"));
			break;
	}
}

void HelloWorld::plugCallback(cocos2d::Ref* pSender)
{

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

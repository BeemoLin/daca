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

	score = 0;
	eq = 0;
	eqArray[0][0] = 3;
	eqArray[0][1] = 0;
	eqArray[1][0] = 1;
	eqArray[1][1] = 0;
	eqArray[2][0] = 2;
	eqArray[2][1] = 0;

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
			CC_CALLBACK_1(HelloWorld::upgradeCallback, this));

	imageItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	eqItem = MenuItemImage::create("eq.png", "eq.png", CC_CALLBACK_1(HelloWorld::eqCallback, this));
	eqItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - eqItem->getContentSize().height));
	eqItem->setTag(tagEqItem);

	plugItem = MenuItemImage::create("plug.png", "plug.png", CC_CALLBACK_1(HelloWorld::plugCallback, this));
	plugItem->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + plugItem->getContentSize().height));
	plugItem->setTag(tagEqItem);

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

	CCString* ns=CCString::createWithFormat("%d",score);
	string score_s=ns->_string;

	auto labelCoin = CCLabelAtlas::create("0", "nums_font.png", 14, 24, '0');
	this->addChild(labelCoin, 1, tagLabelCoin);
	labelCoin->setString(score_s);
	labelCoin->setScale(1);
	labelCoin->setPosition(Vec2(origin.x + 100,
				origin.y + visibleSize.height - labelCoin->getContentSize().height * 2));


	eqStatus = LabelTTF::create("武器名稱", "fonts/Marker Felt.ttf", 24);
	eqStatus->setPosition(Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height - eqStatus->getContentSize().height));
        this->addChild(eqStatus, 1);

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
	this->changeEq(eq);
}

void HelloWorld::updateData(float dt)
{
	score++;
}

void HelloWorld::upgradeCallback(cocos2d::Ref* pSender)
{
    int eqLevel = eqArray[eq][1];

    if(eqLevel<=6)
    {
        srand((unsigned)time(NULL)); //rand seed
        int chance=(rand() % 100) +1;
        int lucky= plug * 50;
        if(chance+lucky>100)
        {
            eqLevel++;
        }

        eqLevel++;
    }
    else if(eqLevel<=8)
    {
        srand((unsigned)time(NULL)); //rand seed
        int chance=(rand() % 100) +1;
        int lucky= plug * 20;
        if(chance+lucky>50)
        {
            eqLevel++;
        }
        else
        {
            eqLevel=0;
        }
    }
    else
    {
        srand((unsigned)time(NULL)); //rand seed
        int chance=(rand() % 100) +1;
        int lucky= plug * 20;
        if(chance+lucky>80)
        {
            eqLevel++;
        }
        else
        {
            eqLevel=0;
        }
    }


    eqArray[eq][1]= eqLevel;
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
}

void HelloWorld::plugCallback(cocos2d::Ref* pSender)
{
  if(plug<1)
  {
      plug++;
  }
  else
  {
      plug = 0;
  }

  switch(plug)
  {
          case 0:
            plugItem->setNormalImage(Sprite::create("plug.png"));
            plugItem->setSelectedImage(Sprite::create("plug.png"));
            break;

          case 1:
            plugItem->setNormalImage(Sprite::create("plug2.png"));
            plugItem->setSelectedImage(Sprite::create("plug2.png"));
            break;

          default:
            plugItem->setNormalImage(Sprite::create("plug.png"));
            plugItem->setSelectedImage(Sprite::create("plug.png"));
            break;
  }
}

void HelloWorld::changeEq(int iEq)
{
  int eqID = eqArray[iEq][0];
  int eqLevel = eqArray[iEq][1];
  CCString* ns=CCString::createWithFormat("%d", eqLevel);
  string sEqLevel=ns->_string;

  switch(eqID)
    {
        case 1:
          eqStatus->setString("+"+sEqLevel+" "+"匕首");
          eqItem->setNormalImage(Sprite::create("eq.png"));
          eqItem->setSelectedImage(Sprite::create("eq.png"));
          break;

        case 2:
          eqStatus->setString("+"+sEqLevel+" "+"匕首(火)");
          eqItem->setNormalImage(Sprite::create("eq2.png"));
          eqItem->setSelectedImage(Sprite::create("eq2.png"));
          break;

        case 3:
          eqStatus->setString("+"+sEqLevel+" "+"匕首(水)");
          eqItem->setNormalImage(Sprite::create("eq3.png"));
          eqItem->setSelectedImage(Sprite::create("eq3.png"));
          break;

        default:
          eqStatus->setString("+"+sEqLevel+" "+"匕首");
          eqItem->setNormalImage(Sprite::create("eq.png"));
          eqItem->setSelectedImage(Sprite::create("eq.png"));
          break;
    }
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

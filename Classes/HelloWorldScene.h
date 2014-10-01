#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define tagLabelCoin 1234
#define tagEqItem 5555
#define tagPlugItem 6666

#include "cocos2d.h"

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
USING_NS_CC;
using namespace std;

class HelloWorld : public cocos2d::Layer
{
	public:
		int score;
		int eq;
		int plug;
		int eqArray [3][2];
		MenuItemImage* eqItem;
		MenuItemImage* plugItem;

		LabelTTF* eqStatus;

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();  

		void update(float dt);

		void updateData(float dt);

		void upgradeCallback(cocos2d::Ref* pSender);

		void eqCallback(cocos2d::Ref* pSender);

		void plugCallback(cocos2d::Ref* pSender);

		void changeEq(int sEq);

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		// implement the "static create()" method manually
		CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

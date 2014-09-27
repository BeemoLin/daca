#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define tagLabelCoin 1234
#define tagEqItem 5555
#define eq1 555
#define eq2 554

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
		MenuItemImage* eqItem;

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();  

		void update(float dt);

		void updateData(float dt);

		// a selector callback
		void eqCallback(cocos2d::Ref* pSender);

		void plugCallback(cocos2d::Ref* pSender);

		// a selector callback
		void menuCloseCallback(cocos2d::Ref* pSender);

		// implement the "static create()" method manually
		CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

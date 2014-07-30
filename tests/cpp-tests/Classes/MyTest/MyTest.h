//
//  MyTest.h
//  cocos2d_tests
//
//  Created by Hector on 14-7-22.
//
//

#ifndef __cocos2d_tests__MyTest__
#define __cocos2d_tests__MyTest__

#include "../testBasic.h"

class MyTestLayer : public Layer
{
public:
    virtual void onEnter() override;
    
	void onTouchesBegan(const std::vector<Touch*>& touches, Event  *event);
    void onTouchesMoved(const std::vector<Touch*>& touches, Event  *event);
    
	Vec2 _beginPos;
    Menu* _itemMenu;
    
	int _testcount;
    
protected:
    void onMouseScroll(Event* event);
};

class MyTestScene : public TestScene
{
public:
    virtual void runThisTest() override;
};

#endif /* defined(__cocos2d_tests__MyTest__) */

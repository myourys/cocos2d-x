//
//  BasicShaderTest.h
//  cocos2d_tests
//
//  Created by Hector on 14-7-25.
//
//

#ifndef __cocos2d_tests__BasicShaderTest__
#define __cocos2d_tests__BasicShaderTest__

#include "../../testBasic.h"
#include "../../BaseTest.h"

class BasicShaderTest: public BaseTest
{
protected:
    TextureAtlas* _atlas;
    
    std::string    _title;
    
public:
    BasicShaderTest(void);
    ~BasicShaderTest(void);
    
    virtual std::string title() const override;
    virtual std::string subtitle() const override;
    void restartCallback(Ref* sender);
    void nextCallback(Ref* sender);
    void backCallback(Ref* sender);
};
/**
 *  灰图
 */
class GrayTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};
/**
 *  负片
 */
class InvertTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};
/**
 *  黑白
 */
class BlackWhiteTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};
/**
 *  浮雕
 */
class ReliefTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};
/**
 *  平滑效果
 */
class SmothTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};
/**
 *  曝光效果
 */
class ExposureTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};
/**
 *  霓虹效果
 */
class NeonTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};

/**
 *  中毒效果
 */
class PoisonTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};
/**
 *  冰冻效果
 */
class FrozenTest : public BasicShaderTest
{
public:
    virtual std::string subtitle() const override;
    virtual void onEnter() override;
};


class BasicShaderTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif /* defined(__cocos2d_tests__BasicShaderTest__) */

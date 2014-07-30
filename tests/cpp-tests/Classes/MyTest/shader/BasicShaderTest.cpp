//
//  BasicShaderTest.cpp
//  cocos2d_tests
//
//  Created by Hector on 14-7-25.
//
//

#include "BasicShaderTest.h"
#include "../../testResource.h"
#include "cocos2d.h"

#define STRINGIFY(A)  #A

const char* s_PositionTextureColor_vert = STRINGIFY(
                                                    
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;

void main()
{
    gl_Position = CC_PMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
}
                                                    
);

Layer* nextBasicShaderTest();
Layer* backBasicShaderTest();
Layer* restartBasicShaderTest();

static int sceneIdx = -1;

#define MAX_LAYER    1

Layer* createBasicShaderTestLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new GrayTest();
    }
    
    return nullptr;
}

Layer* nextBasicShaderTest()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = createBasicShaderTestLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

Layer* backBasicShaderTest()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = createBasicShaderTestLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

Layer* restartBasicShaderTest()
{
    auto layer = createBasicShaderTestLayer(sceneIdx);
    layer->autorelease();
    
    return layer;
}

//------------------------------------------------------------------
//
// BasicShaderTest
//
//------------------------------------------------------------------

BasicShaderTest::BasicShaderTest(void)
{
}

BasicShaderTest::~BasicShaderTest(void)
{
}

std::string BasicShaderTest::title() const
{
    return "BasicShader Test";
}
std::string BasicShaderTest::subtitle() const
{
    return "No title";
}
void BasicShaderTest::restartCallback(Ref* sender)
{
    auto s = new BasicShaderTestScene();
    s->addChild(restartBasicShaderTest());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BasicShaderTest::nextCallback(Ref* sender)
{
    auto s = new BasicShaderTestScene();
    s->addChild( nextBasicShaderTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BasicShaderTest::backCallback(Ref* sender)
{
    auto s = new BasicShaderTestScene();
    s->addChild( backBasicShaderTest() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

//------------------------------------------------------------------
//
// GrayTest
//
//------------------------------------------------------------------

const char* s_TextureGray_flag = STRINGIFY(

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	vec4 v_orColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	float gray = dot(v_orColor.rgb, vec3(0.299, 0.587, 0.114));
	gl_FragColor = vec4(gray, gray, gray, v_orColor.a);
}
                                          
);

void GrayTest::onEnter()
{
    BasicShaderTest::onEnter();

    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto graySprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureGray_flag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    graySprite(right);
}

std::string GrayTest::subtitle() const
{
    return "Test 1. Gray Shader Test";
}


//------------------------------------------------------------------
//
// BasicShaderTestScene
//
//------------------------------------------------------------------

void BasicShaderTestScene::runThisTest()
{
    auto layer = nextBasicShaderTest();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}


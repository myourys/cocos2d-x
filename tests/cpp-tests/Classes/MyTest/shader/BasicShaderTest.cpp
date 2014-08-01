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


Layer* nextBasicShaderTest();
Layer* backBasicShaderTest();
Layer* restartBasicShaderTest();

static int sceneIdx = -1;

#define MAX_LAYER    7

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


Layer* createBasicShaderTestLayer(int nIndex)
{
    switch(nIndex)
    {
        case 0: return new GrayTest();
        case 1: return new InvertTest();
        case 2: return new BlackWhiteTest();
        case 3: return new ReliefTest();
        case 4: return new SmothTest();
        case 5: return new ExposureTest();
        case 6: return new NeonTest();
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

const char* s_TextureGray_frag = STRINGIFY(

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
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureGray_frag);
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
// InvertTest
//
//------------------------------------------------------------------

const char* s_TextureInvert_frag = STRINGIFY(
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	vec4 nomalColor = texture2D(CC_Texture0, v_texCoord);
    gl_FragColor = vec4(1.0 - nomalColor.r,1.0 - nomalColor.b,1.0 - nomalColor.g,1.0);
}
);
                                             
                                        

void InvertTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto InvertSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureInvert_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    InvertSprite(right);
}

std::string InvertTest::subtitle() const
{
    return "Test 2. InvertTest Shader Test";
}

//------------------------------------------------------------------
//
// BlackWhiteTest
//
//------------------------------------------------------------------
const char* s_TextureBlackWhite_frag = STRINGIFY(
    
    varying vec4 v_fragmentColor;
    varying vec2 v_texCoord;
    
    void main()
    {
        vec4 color;
        color = texture2D(CC_Texture0, v_texCoord);
        if ((color.r + color.g + color.b)/3.0 > 100.0/255.0) {
            color.rgb = vec3(1);
        }
        else{
            color.rgb = vec3(0);
        }
        gl_FragColor = vec4(color.rgb, 1);
    }
                                                 
);

void BlackWhiteTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto BlackWhiteSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureBlackWhite_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    BlackWhiteSprite(right);
}

std::string BlackWhiteTest::subtitle() const
{
    return "Test 3. BlackWhiteTest Shader Test";
}

//------------------------------------------------------------------
//
// ReliefTest
//
//------------------------------------------------------------------
const char* s_TextureRelief_frag = STRINGIFY(
varying vec2 v_texCoord;
// image's size
uniform vec2 v_texSize;

void main()
{
    vec2 onePixel = vec2(1.0 / v_texSize.r, 1.0 / v_texSize.g);
    
    vec4 color;
    color.rgb = vec3(0.5);
    color -= texture2D(CC_Texture0, v_texCoord - onePixel) * 5.0;
    color += texture2D(CC_Texture0, v_texCoord + onePixel) * 5.0;
    
    color.rgb = vec3((color.r + color.g + color.b) / 3.0);
    gl_FragColor = vec4(color.rgb, 1);
}
                                                 
);

void ReliefTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto BlackWhiteSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureRelief_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        //glprogram->setUniformLocationWith2f(glprogram->getUniformLocation("v_texSize"),
        //                                    sprite->getContentSize().width, sprite->getContentSize().height);
        glprogramstate->setUniformVec2("v_texSize", sprite->getContentSize());
        sprite->setGLProgramState(glprogramstate);
    };
    
    BlackWhiteSprite(right);
}

std::string ReliefTest::subtitle() const
{
    return "Test 4. ReliefTest Shader Test";
}

//------------------------------------------------------------------
//
// SmothTest
//
//------------------------------------------------------------------
const char* s_TextureSmoth_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
// image's size
uniform vec2 v_texSize;

void main()
{
    vec2 onePixel = vec2(1.0 / v_texSize.r, 1.0 / v_texSize.g);
    
    vec4 nomalColor = texture2D(CC_Texture0, v_texCoord);
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(onePixel.r,0));
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(-onePixel.r,0));
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(0,onePixel.g));
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(0,-onePixel.g));
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(onePixel.r,onePixel.g));
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(onePixel.r,-onePixel.g));
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(-onePixel.r,onePixel.g));
    nomalColor += texture2D(CC_Texture0, v_texCoord + vec2(-onePixel.r,-onePixel.g));
    
    nomalColor.rgb = vec3(nomalColor.rgb / 9.0);
    gl_FragColor = vec4(nomalColor.rgb, 1);
}
);

void SmothTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto BlackWhiteSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureSmoth_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        glprogramstate->setUniformVec2("v_texSize", sprite->getContentSize());
        sprite->setGLProgramState(glprogramstate);
    };
    
    BlackWhiteSprite(right);
}

std::string SmothTest::subtitle() const
{
    return "Test 5. Smoth Shader Test";
}

//------------------------------------------------------------------
//
// SmothTest
//
//------------------------------------------------------------------
const char* s_TextureExposure_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;

void main()
{
    vec4 color= texture2D(CC_Texture0, v_texCoord);
    if (color.r < 128.0/255.0) {
        color.r = 1.0- color.r;
    }
    if (color.g < 128.0/255.0) {
        color.g = 1.0- color.g;
    }
    if (color.b < 128.0/255.0) {
        color.b = 1.0- color.b;
    }
    
    gl_FragColor = vec4(color.rgb, 1);
}
);

void ExposureTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto BlackWhiteSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureExposure_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    BlackWhiteSprite(right);
}

std::string ExposureTest::subtitle() const
{
    return "Test 6. Exposure Shader Test";
}

//------------------------------------------------------------------
//
// NeonTest
//
//------------------------------------------------------------------
const char* s_TextureNeon_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texCoord;
// image's size
uniform vec2 v_texSize;

void main()
{
    vec2 onePixel = vec2(1.0 / v_texSize.r, 1.0 / v_texSize.g);
    
    vec4 color = texture2D(CC_Texture0, v_texCoord);
    vec4 colorRight = texture2D(CC_Texture0, v_texCoord + vec2(0,onePixel.t));
    vec4 colorBottom = texture2D(CC_Texture0, v_texCoord + vec2(onePixel.s,0));
    
    color.r = 3.0* sqrt( (color.r - colorRight.r) * (color.r - colorRight.r) + (color.r - colorBottom.r) * (color.r - colorBottom.r) );
    color.g = 3.0* sqrt( (color.g - colorRight.g) * (color.g - colorRight.g) + (color.g - colorBottom.g) * (color.g - colorBottom.g) );
    color.b = 3.0* sqrt( (color.b - colorRight.b) * (color.b - colorRight.b) + (color.b - colorBottom.b) * (color.b - colorBottom.b) );
    
    color.r >1.0 ? 1.0 : color.r;
    color.g >1.0 ? 1.0 : color.g;
    color.b >1.0 ? 1.0 : color.b;
    gl_FragColor = vec4(color.rgb, 1);
}

);

void NeonTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto BlackWhiteSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureNeon_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        glprogramstate->setUniformVec2("v_texSize", sprite->getContentSize());
        sprite->setGLProgramState(glprogramstate);
    };
    
    BlackWhiteSprite(right);
}

std::string NeonTest::subtitle() const
{
    return "Test 7. Neon Shader Test";
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


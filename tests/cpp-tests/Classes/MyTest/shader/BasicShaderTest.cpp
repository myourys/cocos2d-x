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

#define MAX_LAYER    15

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
        case 7: return new PoisonTest();
        case 8: return new FrozenTest();
        case 9: return new StoneTest();
        case 10: return new BanishTest();
        case 11: return new BlurTest();
        case 12: return new MirrorTest();
        case 13: return new IceTest();
        case 14: return new RGBTest();
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
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureGray_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
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
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureInvert_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
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
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureBlackWhite_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
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
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureRelief_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        //glprogram->setUniformLocationWith2f(glprogram->getUniformLocation("v_texSize"),
        //                                    sprite->getContentSize().width, sprite->getContentSize().height);
        glprogramstate->setUniformVec2("v_texSize", sprite->getContentSize());
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
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
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureSmoth_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        glprogramstate->setUniformVec2("v_texSize", sprite->getContentSize());
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
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
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureExposure_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
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
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureNeon_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        glprogramstate->setUniformVec2("v_texSize", sprite->getContentSize());
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string NeonTest::subtitle() const
{
    return "Test 7. Neon Shader Test";
}


//------------------------------------------------------------------
//
// PoisonTest
//
//------------------------------------------------------------------
const char* s_TexturePoison_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
void main()
{
    gl_FragColor = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
    gl_FragColor.r *= 0.8; 
    gl_FragColor.r += 0.08 * gl_FragColor.a; 
    gl_FragColor.g *= 0.8; 
    gl_FragColor.b *= 0.8; 
    gl_FragColor.g += 0.2 * gl_FragColor.a;
}
                                           );

void PoisonTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TexturePoison_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string PoisonTest::subtitle() const
{
    return "Test 8. Poison Shader Test";
}

//------------------------------------------------------------------
//
// FrozenTest
//
//------------------------------------------------------------------
const char* s_TextureFrozen_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
void main(void)
{
    vec4 normalColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
	normalColor *= vec4(0.8, 0.8, 0.8, 1);
	normalColor.b += normalColor.a * 0.2;
    gl_FragColor = normalColor;
}


);

void FrozenTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureFrozen_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string FrozenTest::subtitle() const
{
    return "Test 9. Frozen Shader Test";
}


//------------------------------------------------------------------
//
// FrozenTest
//
//------------------------------------------------------------------
const char* s_TextureStone_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D u_texture;

void main()
{
    vec4 color1 = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
	float brightness = (color1.r + color1.g + color1.b) * (1. / 3.);
	float gray = (0.6) * brightness;
    gl_FragColor = vec4(gray, gray, gray, color1.a);
}
                                             
                                             );

void StoneTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureStone_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string StoneTest::subtitle() const
{
    return "Test 10. Stone Shader Test";
}


//------------------------------------------------------------------
//
// BanishTest
//
//------------------------------------------------------------------
const char* s_TextureBanish_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	gl_FragColor = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
	float gray = (gl_FragColor.r + gl_FragColor.g + gl_FragColor.b) * (1.0 / 3.0);
	gl_FragColor = vec4(gray * 0.9, gray * 1.2, gray * 0.8, gl_FragColor.a * (gray + 0.1));
}
                                        
);

void BanishTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureBanish_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string BanishTest::subtitle() const
{
    return "Test 11. Banish Shader Test";
}

//------------------------------------------------------------------
//
// BlurTest
//
//------------------------------------------------------------------
const char* s_TextureBlur_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec2 blurSize;

void main() {
   vec4 sum = vec4(0.0);
   vec4 substract = vec4(0,0,0,0);
   
   float alpha = texture2D(CC_Texture0 , v_texCoord).a;
   
   sum += texture2D(CC_Texture0, v_texCoord - 4.0 * blurSize) * 0.05;
   sum += texture2D(CC_Texture0, v_texCoord - 3.0 * blurSize) * 0.09;
   sum += texture2D(CC_Texture0, v_texCoord - 2.0 * blurSize) * 0.12;
   sum += texture2D(CC_Texture0, v_texCoord - 1.0 * blurSize) * 0.15;
   sum += texture2D(CC_Texture0, v_texCoord                 ) * 0.16;
   sum += texture2D(CC_Texture0, v_texCoord + 1.0 * blurSize) * 0.15;
   sum += texture2D(CC_Texture0, v_texCoord + 2.0 * blurSize) * 0.12;
   sum += texture2D(CC_Texture0, v_texCoord + 3.0 * blurSize) * 0.09;
   sum += texture2D(CC_Texture0, v_texCoord + 4.0 * blurSize) * 0.05;
   
   vec4 temp = vec4(0,0,0,0);
   temp = (sum - substract) * v_fragmentColor;
   
   if(alpha < 0.05)
   {
       gl_FragColor = vec4(0 , 0 , 0 , 0);
   }
   else
   {
       gl_FragColor = temp;
   }
}
 );

void BlurTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureBlur_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        glprogramstate->setUniformVec2("blurSize",Vec2( 1.0/ sprite->getContentSize().width,1.0/ sprite->getContentSize().height));
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string BlurTest::subtitle() const
{
    return "Test 12. Blur Shader Test";
}


//------------------------------------------------------------------
//
// MirrorTest
//
//------------------------------------------------------------------
const char* s_TextureMirror_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    vec4 normalColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
    normalColor.r = normalColor.r * 0.5;
    normalColor.g = normalColor.g * 0.8;
    normalColor.b = normalColor.b + normalColor.a * 0.2;
    gl_FragColor = normalColor;
}
                                             
                                          
);

void MirrorTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureMirror_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string MirrorTest::subtitle() const
{
    return "Test 13. Mirror Shader Test";
}

//------------------------------------------------------------------
//
// IceTest
//
//------------------------------------------------------------------
const char* s_TextureIce_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    vec4 color1 = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
	float brightness = (color1.r + color1.g + color1.b) * (1. / 3.);
	float gray = (1.5)*brightness;
	color1 = vec4(gray, gray, gray, color1.a)*vec4(0.8,1.2,1.5,1);
    gl_FragColor =color1;
}
                                             
);

void IceTest::onEnter()
{
    BasicShaderTest::onEnter();
    
    auto left = Sprite::create(s_Power);
    auto right = Sprite::create(s_Power);
    
    left->setPosition(VisibleRect::center() - Vec2(80,0));
    right->setPosition(VisibleRect::center() + Vec2(80,0));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureIce_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
    };
    
    shaderSprite(right);
}

std::string IceTest::subtitle() const
{
    return "Test 14. Ice Shader Test";
}


//------------------------------------------------------------------
//
// RGBTest
//
//------------------------------------------------------------------
const char* s_TextureRGB_frag = STRINGIFY(
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
    vec4 color1 = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
    vec4 color2 = color1;
    color2.rgb = vec3(251.0/255.0,182.0/255.0,52.0/255.0) * color1.r +
    vec3(255.0/255.0,247.0/255.0,153.0/255.0) *  color1.g +
    vec3(149.0/255.0,148.0/255.0,120.0/255.0) * color1.b;
    
    gl_FragColor = color2;
}
                                          
);

void RGBTest::onEnter()
{
    BasicShaderTest::onEnter();
    const char* s_rgb = "mytest/rgb.png";
    auto left = Sprite::create(s_rgb);
    auto right = Sprite::create(s_rgb);
    
    left->setPosition(VisibleRect::center() - Vec2(0,50));
    right->setPosition(VisibleRect::center() + Vec2(0,50));
    this->addChild(left);
    this->addChild(right);
    
    auto shaderSprite = [](Sprite* sprite){
        auto glprogram = GLProgram::createWithByteArrays(s_PositionTextureColor_vert, s_TextureRGB_frag);
        auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
        sprite->setGLProgramState(glprogramstate);
        sprite->getTexture()->setAntiAliasTexParameters();
    };
    
    shaderSprite(right);
}

std::string RGBTest::subtitle() const
{
    return "Test 15. RGB Shader Test";
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


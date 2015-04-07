#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

class MyShape : DrawNode {
    
public:
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags){
        drawLine(Vec2(0, 0), Vec2(100, 100), Color4F::RED);
    }
    virtual bool init(){
        
        return true;
    }
    CREATE_FUNC(MyShape);
};

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
    MyShape * myShape = MyShape::create();
    addChild(myShape);
//    auto rootNode = CSLoader::createNode("MainScene.csb");
//
//    addChild(rootNode);
    
    
    
    return true;
}

#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ImageScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
    
    auto bgSprite = Sprite::create("bg.jpg");
    bgSprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    addChild(bgSprite);
    
    auto label = Label::createWithSystemFont("Start ImageScene", "", 40);
    label->setPosition(visibleSize.width/2,visibleSize.height/2);
    addChild(label);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [label,this](Touch * t , Event * e){
        
        
        return true;
    };
    
    listener->onTouchEnded = [](Touch*t,Event*e){
        
        if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()))
        {
            Director::getInstance()->pushScene(TransitionFadeBL::create(1, ImageScene::createScene()));
        }
        
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
    
    return true;
}

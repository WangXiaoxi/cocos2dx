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
    
    Size size = Director::getInstance()->getVisibleSize();
    TextFieldTTF * tf = TextFieldTTF::textFieldWithPlaceHolder("点击此处输入", "宋体", 20);
    tf->setAnchorPoint(Vec2(0, 0));
    tf->setPosition(size.width/2, size.height/2);
    addChild(tf);
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [tf](Touch *t,Event *event){
//        log("pressed>>>>>>>");
        if (tf->getBoundingBox().containsPoint(t->getLocation())) {
            tf->attachWithIME();
        }else {
            tf->detachWithIME();
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, tf);
    
    return true;
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

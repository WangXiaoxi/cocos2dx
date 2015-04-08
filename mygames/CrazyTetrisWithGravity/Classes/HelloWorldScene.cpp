#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

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
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    Button * buttonExit = dynamic_cast<Button*>(rootNode->getChildByName("buttonExit"));
    
    if (buttonExit)
    {
        log("%s",buttonExit->getName().c_str());
    }
    
    buttonExit->addClickEventListener(buttonCallBack);
    buttonExit->setTag(1011);
    
    Button * button = dynamic_cast<Button*>(rootNode->getChildByName("Button_2"));
    button->addClickEventListener(buttonCallBack);
    return true;
}

void HelloWorld::buttonCallBack(cocos2d::Ref *ref)
{
    Button * btn = dynamic_cast<Button*>(ref);
    int tag = btn->getTag();
    switch (tag) {
        case 1011:
            log("%s",btn->getName().c_str());
            break;
        default:
            Director::getInstance()->end();
            break;
    }
}

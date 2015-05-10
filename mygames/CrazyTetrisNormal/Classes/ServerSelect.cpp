//
//  ServerSelect.cpp
//  CrazyTetris
//
//  Created by wangxi on 15/4/30.
//
//

#include "ServerSelect.h"
#include <CocosGUI.h>
#include <cocostudio/CocoStudio.h>

#include "GameScene.h"
using namespace cocos2d::ui;

Scene * ServerSelect::createScene()
{
    auto scene = Scene::create();
    auto layer = ServerSelect::create();
    scene->addChild(layer);
    return scene;
}

bool ServerSelect::init()
{
    if (!Layer::init())
    {
        return false;
        
    }
    
    auto rootNode = CSLoader::createNode("ServerSelect.csb");
    addChild(rootNode);
    
    auto roomLayer = rootNode->getChildByName("roomLayer");
    Text * room1 = dynamic_cast<Text*>(roomLayer->getChildByName("room1"));
    Text * room2 = dynamic_cast<Text*>(roomLayer->getChildByName("room2"));
    
    Button * back  = dynamic_cast<Button*>(roomLayer->getChildByName("back"));
    
    auto backClickListener = [](Ref*){
        Director::getInstance()->popScene();
    };
    back->addClickEventListener(backClickListener);
    
    
    auto roomClickListener = [](Ref*){
        auto scene = GameScene::createScene();
        Director::getInstance()->pushScene(scene);
    };
    room1->addClickEventListener(roomClickListener);
    
    return true;
}
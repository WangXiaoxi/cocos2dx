//
//  ImageScene.cpp
//  L01StartScene
//
//  Created by nyist-mac1 on 15/4/3.
//
//

#include "ImageScene.h"

Scene * ImageScene::createScene()
{
    
    auto scene = Scene::create();
    auto layer = ImageScene::create();
    scene->addChild(layer);
    return scene;
}

bool ImageScene::init()
{
    Layer::init();
    visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    addChild(sprite);
    
    auto exit = Label::createWithSystemFont("Exit", "", 20);
    exit->setPosition(100,100);
    addChild(exit);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [exit](Touch*t,Event*e){
        
        Director::getInstance()->popScene();
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, exit);
    
    return true;
}

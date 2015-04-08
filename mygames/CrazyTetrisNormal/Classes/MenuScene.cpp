//
//  MenuScene.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/3/5.
//
//

#include "MenuScene.h"
#include <cocostudio/CocoStudio.h>
#include <CocosGUI.h>

#include "GameScene.h"

using namespace cocos2d::ui;



Scene * MenuScene::createScene()
{
    auto scene = Scene::create();
    auto menuScene = MenuScene::create();
    scene->addChild(menuScene);
    return scene;
}

bool MenuScene::init()
{
    
    if (!Layer::init())
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MenuScene.csb");
    
    if (rootNode)
    {
        addChild(rootNode);
    }
    
    Text * startGame = dynamic_cast<Text*>(rootNode->getChildByName("startGame"));
    startGame->setTag(ClickTag::START_GAME);
    Text * exitGame = dynamic_cast<Text*>(rootNode->getChildByName("exitGame"));
    exitGame->setTag(ClickTag::EXIT_GAME);
    
    startGame->addClickEventListener(clickCallback);
    exitGame->addClickEventListener(clickCallback);
    
    return true;
}

void MenuScene::clickCallback(cocos2d::Ref *ref)
{
    Node * node = dynamic_cast<Node*>(ref);
    int tag = node->getTag();
    switch (tag) {
        case ClickTag::START_GAME:
            Director::getInstance()->pushScene(TransitionFade::create(0.5, GameScene::createScene()));
            break;
        case ClickTag::EXIT_GAME:
            Director::getInstance()->end();
            break;
        default:
            break;
    }
}
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
#include "HeroListScene.h"
#include "ServerSelect.h"

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
    Text * startGameDuoblePlayer = dynamic_cast<Text*>(rootNode->getChildByName("startGameDoublePlayer"));
    startGameDuoblePlayer->setTag(ClickTag::START_GAME_DOUBLE_PLAYER);
    Text * heroList = dynamic_cast<Text*>(rootNode->getChildByName("heroList"));
    heroList->setTag(ClickTag::HERO_LIST);
    
    
    startGame->addClickEventListener(clickCallback);
    startGameDuoblePlayer->addClickEventListener(clickCallback);
    heroList->addClickEventListener(clickCallback);
    exitGame->addClickEventListener(clickCallback);
    
    
    return true;
}

void MenuScene::clickCallback(cocos2d::Ref *ref)
{
    Node * node = dynamic_cast<Node*>(ref);
    int tag = node->getTag();
    switch (tag) {
            //单人游戏
        case ClickTag::START_GAME:
        {
            //设置用户首选项数据为单机版
            UserDefault::getInstance()->setBoolForKey("isNetWork", false);
            Director::getInstance()->pushScene(TransitionFade::create(0.5, GameScene::createScene()));
        }
            break;
            //双人游戏
        case ClickTag::START_GAME_DOUBLE_PLAYER:
        {   //设置用户首选项数据为对战版
            UserDefault::getInstance()->setBoolForKey("isNetWork", true);
            Director::getInstance()->pushScene(TransitionFade::create(0.5, ServerSelect::createScene()));
        }
            break;
        case ClickTag::HERO_LIST:
            Director::getInstance()->pushScene(TransitionFade::create(0.5, HeroListScene::createScene()));
            break;
        case ClickTag::EXIT_GAME:
            Director::getInstance()->end();
            break;
        default:
            break;
    }
}
//
//  HeroListScene.cpp
//  CrazyTetris
//
//  Created by wangxi on 15/4/29.
//
//

#include "HeroListScene.h"
#include <CocosGUI.h>
#include <cocostudio/CocoStudio.h>

using namespace cocos2d::ui;

Scene * HeroListScene::createScene()
{
    auto scene = Scene::create();
    auto heroList = HeroListScene::create();
    scene->addChild(heroList);
    return scene;
}

bool HeroListScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("HeroListScene.csb");
    addChild(rootNode);
    
    
    Text *rankText[8];
    auto rankLayer = rootNode->getChildByName("ranklayer");
    for (int i = 0; i<8; i++)
    {
        auto name = StringUtils::format("rank%d",i);
        rankText[i] = dynamic_cast<Text*>(rankLayer->getChildByName(name.c_str()));
    }
    
    Text * mainPage = dynamic_cast<Text*>(rootNode->getChildByName("mainPage"));
    
    auto callback = [](Ref*){
        Director::getInstance()->popScene();
    };
    mainPage->addClickEventListener(callback);
    
    auto ranking =  Ranking::getRankingData();
    
    
    
    for (int i = 0;i<8; i++)
    {
        if (!rankText[i])
        {
            break;
        }
        auto text = rankText[i]->getString();
        auto scoreStr = StringUtils::format("%s%d分",text.c_str(),ranking.at(i).asInt());
        rankText[i]->setString(scoreStr);
    }
    
    return true;
}
//
//  HeroListScene.cpp
//  CrazyTetris
//
//  Created by wangxi on 15/4/29.
//
//

#include "HeroListScene.h"

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
    
    return true;
}
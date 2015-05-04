//
//  ServerSelect.cpp
//  CrazyTetris
//
//  Created by wangxi on 15/4/30.
//
//

#include "ServerSelect.h"
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
    
    return true;
}
//
//  BlockNode.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#include "BlockNode.h"

bool BlockNode::initWithArgs(std::string filename)
{
    Sprite * sprite = Sprite::create(filename);
    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(sprite);
    log("BlockNode ::: method initWithArgs1 is called!");
    return true;
}

bool BlockNode::initWithArgs(cocos2d::Color4F color)
{
    log("BlockNode ::: method initWithArgs2 is called!");
    dn->drawRect(Vec2::ZERO, Vec2(NODE_WIDTH, NODE_HEIGHT), color);
    addChild(dn);
    return true;
}

bool BlockNode::init()
{
    
    isExist = true;
    dn = DrawNode::create();
    log("BlockNode :::: method init is called!");
    setContentSize(Size(NODE_WIDTH, NODE_HEIGHT));

    return true;
}
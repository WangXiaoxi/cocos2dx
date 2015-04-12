//
//  IBlock.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#include "IBlock.h"
bool IBlock::init()
{

    BaseBlock::init();
    sprite = Sprite::create();
    sprite->setColor(Color3B::RED);
    sprite->setContentSize(Size(NODE_WIDTH*4,NODE_HEIGHT*4));
    sprite->setTextureRect(Rect(0, 0, NODE_WIDTH*4, NODE_HEIGHT*4));
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(Vec2::ZERO);
    addChild(sprite);
    blockNode1 = BlockNode::create();
    blockNode1->initWithArgs(Color4F::RED);
    blockNode1->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, 0+NODE_HEIGHT/2));
    addChild(blockNode1);
    
    BlockNode * blockNode2 = BlockNode::create();
    blockNode2->initWithArgs(Color4F::BLUE);
    blockNode2->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2,NODE_HEIGHT+NODE_HEIGHT/2));
    addChild(blockNode2);
    
    BlockNode * blockNode3 = BlockNode::create();
    blockNode3->initWithArgs(Color4F::YELLOW);
    blockNode3->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2));
    addChild(blockNode3);
    
    BlockNode * blockNode4 = BlockNode::create();
    blockNode4->initWithArgs(Color4F::WHITE);
    blockNode4->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*3+NODE_HEIGHT/2));
    addChild(blockNode4);
    
    setColor(Color3B::RED);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    log("Size/ width:%f,height:%f",getContentSize().width,getContentSize().height);
    log("anX:%f,anY:%f",getAnchorPoint().x,getAnchorPoint().y);
    
    return true;
}

Point IBlock::getWorldSpace()
{
    return convertToWorldSpace(blockNode1->getPosition());
}

void IBlock::setRotation90()
{
    rotateTimes++;
    setRotation(90*rotateTimes);
}
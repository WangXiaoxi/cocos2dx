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
    node = Node::create();
    BaseBlock::init();
    BlockNode * blockNode1 = BlockNode::create();
    blockNode1->initWithArgs(Color4F::RED);
    blockNode1->setPosition(Vec2(NODE_WIDTH, 0));
    node->addChild(blockNode1);
    
    BlockNode * blockNode2 = BlockNode::create();
    blockNode2->initWithArgs(Color4F::BLUE);
    blockNode2->setPosition(Vec2(NODE_WIDTH,NODE_HEIGHT));
    node->addChild(blockNode2);
    
    BlockNode * blockNode3 = BlockNode::create();
    blockNode3->initWithArgs(Color4F::YELLOW);
    blockNode3->setPosition(Vec2(NODE_WIDTH, NODE_HEIGHT*2));
    node->addChild(blockNode3);
    
    BlockNode * blockNode4 = BlockNode::create();
    blockNode4->initWithArgs(Color4F::GREEN);
    blockNode4->setPosition(Vec2(NODE_WIDTH, NODE_HEIGHT*3));
    node->addChild(blockNode4);
    node->setAnchorPoint(Vec2(0.375, 0.625));
    node->setColor(Color3B::BLUE);
    addChild(node);
    
    
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    log("Size/ width:%f,height:%f",getContentSize().width,getContentSize().height);
    log("anX:%f,anY:%f",getAnchorPoint().x,getAnchorPoint().y);
    
    return true;
}

void IBlock::setRotation90()
{
    rotateTimes++;
    node->setRotation(90*rotateTimes);
}
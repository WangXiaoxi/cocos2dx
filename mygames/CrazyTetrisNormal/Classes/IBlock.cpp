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
    BaseBlock::initWithColor(Color4F::RED);
    nodes->at(0)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, 0+NODE_HEIGHT/2));
    addChild(nodes->at(0));
    

    nodes->at(1)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2,NODE_HEIGHT+NODE_HEIGHT/2));
    addChild(nodes->at(1));
    

    nodes->at(2)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2));
    addChild(nodes->at(2));
    

    nodes->at(3)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*3+NODE_HEIGHT/2));
    addChild(nodes->at(3));
    
    
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    return true;
}

Point IBlock::getWorldSpace(BlockNode*node)
{
    return convertToWorldSpace(node->getPosition());
}

void IBlock::setRotation90()
{
    rotateTimes++;
    setRotation(90*rotateTimes);
}
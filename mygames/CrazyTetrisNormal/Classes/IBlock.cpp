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
//    nodes->at(0)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, 0+NODE_HEIGHT/2));
//    addChild(nodes->at(0));

    INIT_NODES_POSITION_BY_TAG(0, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT/2);

//    nodes->at(1)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2,NODE_HEIGHT+NODE_HEIGHT/2));
//    addChild(nodes->at(1));
    INIT_NODES_POSITION_BY_TAG(1, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT+NODE_HEIGHT/2);
    

//    nodes->at(2)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2));
//    addChild(nodes->at(2));
    INIT_NODES_POSITION_BY_TAG(2, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2);

//    nodes->at(3)->setPosition(Vec2(NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*3+NODE_HEIGHT/2));
//    addChild(nodes->at(3));
    INIT_NODES_POSITION_BY_TAG(3, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*3+NODE_HEIGHT/2);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    return true;
}

//Point IBlock::getWorldSpace(BlockNode*node)
//{
//    return convertToWorldSpace(node->getPosition());
//}

//void IBlock::setRotation90()
//{
//    rotateTimes++;
//    setRotation(90*rotateTimes);
//}
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
//    BaseBlock::initWithColor(Color4F::RED);
    blockFileName = "绿色.png";
    BaseBlock::initWithFile(blockFileName);
    
    INIT_NODES_POSITION_BY_TAG(0, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(1, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(2, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(3, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*3+NODE_HEIGHT/2);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    return true;
}

Vec2 IBlock::getBornPosition()
{
    return bornPosition;
}

void IBlock::setRotation90()
{
    if (isRotated)
    {
        setRotation(0);
    }else
    {
        setRotation(90);
    }
    isRotated = !isRotated;
}

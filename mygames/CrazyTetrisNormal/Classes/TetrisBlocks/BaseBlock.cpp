//
//  Block.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#include "BaseBlock.h"

bool BaseBlock::init()
{
    setContentSize(Size(NODE_WIDTH*4,NODE_HEIGHT*4));
    nodes = new Vector<BlockNode*>;
    
    for (int i = 0; i<4; i++)
    {
        BlockNode * node = BlockNode::create();
        node->initWithArgs(Color4F::RED);
        nodes->pushBack(node);
    }
    
//    schedule(schedule_selector(BaseBlock::updateBlock), 1);
    
    return true;
}

//bool BaseBlock::initWithMatris(int [4][4] *matris)
//{
//    return true;
//}

void BaseBlock::setRotation90()
{
    rotateTimes++;
    setRotation(90*rotateTimes);
}

void BaseBlock::updateBlock(float dt)
{
    setPosition(getPosition()-Point(0,NODE_HEIGHT));
}

void BaseBlock::moveLeft()
{
    setPosition(getPosition()+Point(-NODE_WIDTH,0));
}

void BaseBlock::moveRight()
{
    setPosition(getPosition()+Point(NODE_WIDTH,0));
}

void BaseBlock::moveDown()
{
    setPosition(getPosition()-Point(0,NODE_HEIGHT));
}

void BaseBlock::moveDownIMD()
{
    setPosition(getPosition()+Point(0,NODE_HEIGHT));
}

Point BaseBlock::getWorldSpace()
{
    return Point(0,0);
}
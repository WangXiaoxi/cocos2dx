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
    bornPosition = Vec2(GAME_VIEW_WIDTH/2, GAME_VIEW_HEIGHT+NODE_HEIGHT);
    setContentSize(Size(NODE_WIDTH*4,NODE_HEIGHT*4));
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    nodes = new Vector<BlockNode*>;
    for (int i = 0; i<4; i++)
    {
        BlockNode * node = BlockNode::create();
        nodes->pushBack(node);
    }
    return true;
}

bool BaseBlock::initWithColor(Color4F color)
{
    for(auto it = nodes->begin();it!=nodes->end();it++)
    {
        (*it)->initWithArgs(color);
    }
//    schedule(schedule_selector(BaseBlock::updateBlock), 1);
    return true;
}

bool BaseBlock::initWithFile(std::string &filename)
{
    for(auto it = nodes->begin();it!=nodes->end();it++)
    {
        
    }
    return true;
}


void BaseBlock::setBlockSchedule(float dt)
{
    if (dt==0)
    {
        unschedule(schedule_selector(BaseBlock::updateBlock));
    }else{
        schedule(schedule_selector(BaseBlock::updateBlock), dt);
    }
}

//此方法已废弃
CC_DEPRECATED_ATTRIBUTE bool BaseBlock::initWithMatris(int matris[][4])
{
    for (int i = 0; i < 4; i ++)
    {
        for (int j = 0 ; j < 4 ; j ++)
        {
            if (matris[i][j]==1)
            {
                
            }
        }
    }
    return true;
}
void BaseBlock::setRotatedTAG(int mTag)
{
    rotatedTAG = mTag;
}

int BaseBlock::getRotatedTAG()
{
    return rotatedTAG;
}

Vector<BlockNode*> * BaseBlock::getNodes()
{
    return nodes;
}

void BaseBlock::setBornPosition(Vec2 position)
{
    bornPosition = position;
}

Vec2 BaseBlock::getBornPosition()
{
    return Vec2(GAME_VIEW_WIDTH/2, GAME_VIEW_HEIGHT+NODE_HEIGHT);
}

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

Point BaseBlock::getNodeWorldSpace(BlockNode*node)
{
    return convertToWorldSpace(node->getPosition());
}
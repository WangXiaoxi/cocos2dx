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
    
//    schedule(schedule_selector(BaseBlock::updateBlock), 1);
    sprite = Sprite::create();
    sprite->setColor(Color3B::RED);
    sprite->setContentSize(Size(NODE_WIDTH*4,NODE_HEIGHT*4));
    sprite->setTextureRect(Rect(0, 0, NODE_WIDTH*4, NODE_HEIGHT*4));
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(Vec2::ZERO);
    addChild(sprite);
    return true;
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
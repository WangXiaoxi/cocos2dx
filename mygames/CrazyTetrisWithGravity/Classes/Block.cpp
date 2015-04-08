//
//  Block.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/3/8.
//
//

#include "Block.h"

static std::string blocks[2] = {"1.png","3.png"};


Block * Block::createBlock()
{
    Block *b = Block::create();
    b->setTexture(blocks[rand()%3-1]);
    return b;
}

Block * Block::createBlock(cocos2d::Size size)
{
    Block *b = Block::create();
    b->setContentSize(size);
    return b;
}

Block * Block::createBlock(std::string name)
{
    Block *b = Block::create();
    b->setTexture(name);
    return b;
}

bool Block::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    rotateCounts = 0;
    return true;
}

void Block::rsetRotation(float rotate)
{
    log("Block :: setRotation is called");
    
    Sprite::setRotation(rotate * rotateCounts);
}
void Block::moveLeft(float offset)
{
    setPosition(getPositionX()-offset,getPositionY());
    return;
}

void Block::moveRight(float offset)
{
    setPosition(getPositionX()+offset,getPositionY());
}

void Block::rotateBlock()
{
    rotateCounts ++;
    setRotation(90 * rotateCounts);
}

void Block::moveDown()
{
    
}

void Block::moveDownIMD()
{
    
}
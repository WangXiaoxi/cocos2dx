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
    return true;
}

void BaseBlock::setRotation90()
{
    setRotation(90*rotateTimes);
}

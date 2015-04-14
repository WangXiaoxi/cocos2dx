//
//  LBlock.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#include "LBlock.h"
bool LBlock::init()
{
    BaseBlock::init();
    BaseBlock::initWithColor(Color4F::BLUE);
//    INIT_NODES_POSITION_BY_TAG(0, NODE_WIDTH, __Y__)
    
//    nodes->at(0)->setPosition(Vec2(float xx, float yy))
    
    return true;
}
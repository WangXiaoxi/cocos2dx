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
    
    sprite = Sprite::create();
    sprite->setTextureRect(Rect(0, 0, NODE_WIDTH*3, NODE_HEIGHT*3));
    sprite->setPosition(Vec2(NODE_WIDTH*1.5, NODE_HEIGHT*1.5));
    addChild(sprite);
    
    setContentSize(Size(NODE_WIDTH*3,NODE_HEIGHT*3));
    INIT_NODES_POSITION_BY_TAG(0, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(1, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*1+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(2, NODE_WIDTH+NODE_WIDTH/2, NODE_HEIGHT*0+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(3, NODE_WIDTH*2+NODE_WIDTH/2, NODE_HEIGHT*0+NODE_HEIGHT/2);
//    nodes->at(0)->setPosition(Vec2(float xx, float yy))
    
    return true;
}
//
//  QBlock.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#include "QBlock.h"
bool QBlock::init()
{
    BaseBlock::init();
    BaseBlock::initWithColor(Color4F::YELLOW);
    
    INIT_NODES_POSITION_BY_TAG(0, NODE_WIDTH*1+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(1, NODE_WIDTH*1+NODE_WIDTH/2, NODE_HEIGHT*1+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(2, NODE_WIDTH*2+NODE_WIDTH/2, NODE_HEIGHT*2+NODE_HEIGHT/2);
    INIT_NODES_POSITION_BY_TAG(3, NODE_WIDTH*2+NODE_WIDTH/2, NODE_HEIGHT*1+NODE_HEIGHT/2);
    return true;
}
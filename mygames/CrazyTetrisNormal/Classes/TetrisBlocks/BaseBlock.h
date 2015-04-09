//
//  Block.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//方块的基类

#ifndef __CrazyTetris__Block__
#define __CrazyTetris__Block__

#include <stdio.h>
#include <cocos2d.h>
#include "BlockNode.h"

USING_NS_CC;

class BaseBlock : public Node
{
protected:
    int rotateTimes=0;
protected:
    Sprite * sprite;
    BlockNode nodes[4][4];
public:
    virtual bool init();
    void setRotation90();
    CREATE_FUNC(BaseBlock);
    
    
};

#endif /* defined(__CrazyTetris__Block__) */

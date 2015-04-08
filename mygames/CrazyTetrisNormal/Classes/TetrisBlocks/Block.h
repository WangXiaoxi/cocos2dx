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

USING_NS_CC;

class Block : public Sprite{
    
public:
    virtual bool init();
    CREATE_FUNC(Block);
};

#endif /* defined(__CrazyTetris__Block__) */

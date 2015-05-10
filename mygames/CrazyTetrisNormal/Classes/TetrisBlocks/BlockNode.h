//
//  BlockNode.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//组成方块的基本节点

#ifndef __CrazyTetris__BlockNode__
#define __CrazyTetris__BlockNode__

#include <stdio.h>
#include <cocos2d.h>
#include "MacroData.h"


USING_NS_CC;

class BlockNode : public Node
{

private:
    bool isExist;
    DrawNode * dn; // 画笔
    
public:
    
    virtual bool init();
    virtual bool initWithArgs(std::string filename);
    virtual bool initWithArgs(Color4F color);
    bool setNodeColor(Color3B color);
    virtual bool moveDown();
    virtual bool moveUp();
    CREATE_FUNC(BlockNode);
};

#endif /* defined(__CrazyTetris__BlockNode__) */

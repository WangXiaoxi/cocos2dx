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
    //记录旋转的角度
    int rotateTimes=0;
protected:
    Sprite * sprite;
    Vector<BlockNode*> *nodes;
public:
    virtual bool init();
    void setRotation90();
    CREATE_FUNC(BaseBlock);
    //根据二位矩阵生成矩阵所对应的Block
    bool initWithMatris(int[4][4]);
    virtual Point getWorldSpace();
    
    
/*操作方法*/
public:
    //自动更新方法
    virtual void updateBlock(float dt);
    //向左移动
    virtual void moveLeft();
    //向右移动
    virtual void moveRight();
    //向下移动
    virtual void moveDown();
    //立即下落
    virtual void moveDownIMD();
    
    
};

#endif /* defined(__CrazyTetris__Block__) */

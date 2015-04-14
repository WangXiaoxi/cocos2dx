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

#define INIT_NODES_POSITION_BY_TAG(__TAG__,__X__,__Y__)\
nodes->at(__TAG__)->setPosition(Vec2(__X__,__Y__));\
addChild(nodes->at(__TAG__));

class BaseBlock : public Node
{
protected:
    //记录旋转的角度
    int rotateTimes=0;
    //记录是否被旋转过
    bool isRotated = false;
protected:
    Vec2 bornPosition;
    Sprite * sprite;
    Vector<BlockNode*> *nodes;
public:
    virtual bool init();
    virtual bool initWithColor(Color4F);
    virtual bool initWithFile(std::string &filename);
    virtual void setRotation90();
    CREATE_FUNC(BaseBlock);
    //根据二位矩阵生成矩阵所对应的Block
    CC_DEPRECATED_ATTRIBUTE bool initWithMatris(int[][4]);
    virtual Point getNodeWorldSpace(BlockNode*);

public:
    Vector<BlockNode*> * getNodes();
    virtual void setBornPosition(Vec2);
    virtual Vec2 getBornPosition();
/*操作方法*/
public:
    virtual void setBlockSchedule(float);
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

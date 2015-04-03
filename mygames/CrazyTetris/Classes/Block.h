//
//  Block.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/3/8.
//
//

#ifndef __CrazyTetris__Block__
#define __CrazyTetris__Block__

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class Block : public Sprite {

    
private:
    int rotateCounts;
    PhysicsBody * body;;
    
public:
    void moveLeft(float );              //向左移动
    void moveRight(float );             //向右移动
    void rotateBlock();                 //旋转方块
    void moveDown();                    //加速下落
    void moveDownIMD();                 //立即下落
    
public:
    
    static Block * createBlock();
    static Block * createBlock(Size);
    static Block * createBlock(std::string name);
    
    virtual bool init();
    
    CREATE_FUNC(Block);
    
    void rsetRotation(float);
    
};


#endif /* defined(__CrazyTetris__Block__) */

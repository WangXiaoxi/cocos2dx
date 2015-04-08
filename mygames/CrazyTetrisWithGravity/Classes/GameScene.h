//
//  GameScene.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/3/5.
//
//

#ifndef __CrazyTetris__GameScene__
#define __CrazyTetris__GameScene__

#include <cocos2d.h>
#include <CocosGUI.h>

#include "Block.h"


USING_NS_CC;


using namespace cocos2d::ui;

class GameScene : public Layer {

private:
    //方块出生位置
    Vec2  bornPosition;
    //可视区域大小
    Size visibleSize;
    //游戏暂停状态
    bool running = true;
private:
    
    Block *currentBlock;        //当前的方块
    Block *nextBlock;           //下一个方块
    
    Button * btnPause;          //暂停
    Button * btnBack;           //返回
    Button * btnLeft;           //向左移动
    Button * btnRight;          //向右移动
    Button * btnRotate;         //旋转
    Button * btnDown;           //加速下落
    Button * btnDownIMD;        //立即下落
    
    Layer * gameViewLayer;
    Layer * nextBlockLayer;
    
public:
    
    void gamePause();
    void gameStart();
    void gameBack();
    
    //按钮枚举类型
    enum ClickButton
    {
        PAUSE,
        BACK,
        RIGHT,
        LEFT,
        ROTATE,
        DOWN,
        DOWN_IMD
    };
    
public:
    static PhysicsWorld * world;
    static Scene * createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
    void addCurrentBlock(float x, float y);
    void addCurrentBlock(Vec2 position);
};

#endif /* defined(__CrazyTetris__GameScene__) */

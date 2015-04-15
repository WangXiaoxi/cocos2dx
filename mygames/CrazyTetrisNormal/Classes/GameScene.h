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

#include "BaseBlock.h"

#include "MacroData.h"

USING_NS_CC;


using namespace cocos2d::ui;

class GameScene : public Layer {

private:
    BaseBlock * currentBlock;//当前操作方块
    BaseBlock * nextBlock;//下一个方块
    
    Vector<BlockNode*> *fallenNodes; // 已经落下的方块
private:
    //当前方块的位置
    Vec2 currentBlockPositon;
    //方块出生位置
    Vec2 bornPosition;
    //下一个方块的的位置
    Vec2 nextBlockPosition;
    //可视区域大小
    Size visibleSize;
    //游戏暂停状态
    bool running = true;
private:
    
    Button * btnPause;          //暂停
    Button * btnBack;           //返回
    Button * btnLeft;           //向左移动
    Button * btnRight;          //向右移动
    Button * btnRotate;         //旋转
    Button * btnDown;           //加速下落
    Button * btnDownIMD;        //立即下落
    
    Layer * gameViewLayer; //游戏区域Layer
    
    Layer * nextBlockLayer; //待下落区域Layer
    
    //游戏逻辑方法
private:
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
public:
    //添加一个新的方块
    void addNewBlock();
    //生成一个方块
    BaseBlock * createNewBlock();
    //碰撞检测
    void blockCollide();
    //消除行
    void deleteCompleteLine();
    //检测是否游戏结束
    bool isGameOver();
    //游戏界面外
    virtual bool isOutofGameView();
public:
    void gameStart();
    void update(float);
    void gamePause();
    void gameReStart();
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

    static Scene * createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
};

#endif /* defined(__CrazyTetris__GameScene__) */

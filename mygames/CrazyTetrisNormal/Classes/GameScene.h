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
#include "ODSocket/ODSocket.h"
#include "MacroData.h"
#include <cocos/audio/include/SimpleAudioEngine.h>
USING_NS_CC;


using namespace cocos2d::ui;
using namespace CocosDenshion;

class GameScene : public Layer {
//游戏属性
private:
    float BLOCK_STOP = 0;   //方块停止
    float BLOCK_SPEED = 1;  //方块下落速度
    
private:
    SimpleAudioEngine * audio;//音乐播放引擎
    bool musicOn = true;
    
private:
    
    BaseBlock * currentBlock;//当前操作方块
    BaseBlock * nextBlock;//下一个方块
    
    Vector<BlockNode*> *fallenNodes; // 已经落下的方块
    Vector<BlockNode*> *lines[20];  //行数
//    Vector<Vector<BlockNode*>*>* fallen;//已经下落的方块
    
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
    int score=0;                //得分
    Text * scoreText;           //积分板
    
    Button * btnPause;          //暂停
    Button * btnBack;           //返回
    Button * btnLeft;           //向左移动
    Button * btnRight;          //向右移动
    Button * btnRotate;         //旋转
    Button * btnDown;           //加速下落
    Button * btnDownIMD;        //立即下落
    Button * btnMusic;          //音效控制
    
    Layer * gameViewLayer; //游戏区域Layer
    
    Layer * nextBlockLayer; //待下落区域Layer
    
    //游戏逻辑方法
private:
    bool canMoveLeft();
    bool canMoveRight();
    bool canMoveDown();
    //网络连接
public:
    ODSocket socket;
    bool isNetWork;
    bool connectServer();
    void receiveData();
    void sendData();
public:
    //添加一个新的方块
    void addNewBlock();
    //生成一个方块
    BaseBlock * createNewBlock(BaseBlock*);
    //碰撞检测
    void blockCollide();
    //消除行
    void deleteCompleteLine();
    //检测是否游戏结束
    bool isGameOver();
    //更新分数
    void updateScore(int);
    //加载英雄榜
    void loadRankingData();
    //更新英雄榜
    void updateRanking();
    //游戏界面外
    virtual bool isOutofGameView();
    //添加一行新的方块
    virtual void addBottmBlocks();

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
        DOWN_IMD,
        MUSIC
    };
    
public:

    static Scene * createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
    
};

#endif /* defined(__CrazyTetris__GameScene__) */

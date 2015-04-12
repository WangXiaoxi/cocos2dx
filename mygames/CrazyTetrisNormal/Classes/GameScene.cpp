//
//  GameScene.cpp
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/3/5.
//
//

#include "GameScene.h"
#include <cocostudio/CocoStudio.h>
#include <CocosGUI.h>

/**************************************/
#include "BlockNode.h"
#include "IBlock.h"
/**************************************/

#define INIT_BUTTON(__VAR__,__ROOT__,__NAME__,__TAG__,__CLICK_CALLBACK__) \
__VAR__ = static_cast<Button*>(__ROOT__->getChildByName(__NAME__)); \
__VAR__ -> setTag(__TAG__); \
__VAR__ -> addClickEventListener(__CLICK_CALLBACK__);

#define CONTACT_BIT_MASK_EDGE           0b1000
#define CONTACT_BIT_MASK_CURRENT_BLOCK  0b0100


//#define UNIT_WIDTH Director::getInstance()->getVisibleSize().width/10
#define UNIT_WIDTH gameViewLayer->getContentSize().width/10

using namespace cocos2d::ui;


Scene * GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

//画出背景上的灰色格子
void drawGameLayerLines(Layer * gameLayer)
{
    DrawNode * drawNode = DrawNode::create();
    for (int i = 0;i<21 ;i++ )
    {
        drawNode->drawLine(Vec2(0, i*NODE_HEIGHT), Vec2(GAME_VIEW_WIDTH, i*NODE_HEIGHT), Color4F::GRAY);
    }
    for (int i = 0; i<11; i++)
    {
        drawNode->drawLine(Vec2(i*NODE_WIDTH,0), Vec2(i*NODE_WIDTH, GAME_VIEW_HEIGHT), Color4F::GRAY);
    }
    drawNode->drawRect(Vec2::ZERO, Vec2(GAME_VIEW_WIDTH, GAME_VIEW_HEIGHT), Color4F::BLACK);
    gameLayer->addChild(drawNode);
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    //游戏数据初始化
    visibleSize = Director::getInstance()->getVisibleSize();
    //添加通过CocosStudio制作的游戏场景到当前Scene中
    auto rootNode = CSLoader::createNode("GameScene.csb");
    addChild(rootNode);
    
    //初始化游戏场景，获取游戏区域和下一块方块的的区域
    gameViewLayer = static_cast<Layer*>(rootNode->getChildByName("gameLayer"));
    nextBlockLayer = static_cast<Layer*>(rootNode->getChildByName("nextLayer"));
    
    drawGameLayerLines(gameViewLayer);
    
    log("%f",gameViewLayer->getContentSize().width);
    
    BlockNode * node = BlockNode::create();
    node->initWithArgs("1.png");
    nextBlockLayer->addChild(node);
    node->setPosition(Vec2(nextBlockLayer->getContentSize().width/2, nextBlockLayer->getContentSize().height/2));
    
    
    currentBlock = IBlock::create();
    currentBlock->setPosition(Vec2::ZERO);
    gameViewLayer->addChild(currentBlock);
    
    Vec2 vec1 = gameViewLayer->convertToNodeSpace(currentBlock->getWorldSpace());
    log("node1.x:%f,node1.y%f",vec1.x,vec1.y);
    
    log("WIDTH:%f,HEIGHT:%f",gameViewLayer->getContentSize().width,gameViewLayer->getContentSize().height);
    
        //定义按钮监听器
    ui::Widget::ccWidgetClickCallback btnClickCallback = [this](Ref * ref)
        {
            Button * btn = static_cast<Button*>(ref);
            switch (btn->getTag()) {
                case PAUSE:
                {
                    this->running?this->gamePause():this->gameStart();
                    running = !running;
                }
                    break;
                case BACK:
                    this->gameBack();
                    break;
                case LEFT:
                    currentBlock->moveLeft();
                    break;
                case RIGHT:
                    currentBlock->moveRight();
                    break;
                case ROTATE:
                    currentBlock->setRotation90();
                    break;
                case DOWN:
                    currentBlock->moveDown();
                    break;
                case DOWN_IMD:
                    currentBlock->moveDownIMD();
                    break;
                    
                default:
                    break;
            }
        };
    
    //初始化游戏场景内的按钮
    INIT_BUTTON(btnPause, rootNode, "pauseButton", PAUSE , btnClickCallback);
    INIT_BUTTON(btnBack, rootNode, "backButton", BACK, btnClickCallback);
    INIT_BUTTON(btnLeft, rootNode, "leftButton", LEFT, btnClickCallback);
    INIT_BUTTON(btnRight, rootNode, "rightButton", RIGHT, btnClickCallback);
    INIT_BUTTON(btnRotate, rootNode, "rotateButton", ROTATE, btnClickCallback);
    INIT_BUTTON(btnDown, rootNode, "downButton", DOWN, btnClickCallback);
    INIT_BUTTON(btnDownIMD, rootNode, "downButtonIMD", DOWN_IMD, btnClickCallback);

    scheduleUpdate();
    
    return true;
}

void GameScene::gamePause()
{
    log("pause");
    Director::getInstance()->pause();
//    world->getAllBodies()
}
void GameScene::gameStart()
{
    log("start");
    Director::getInstance()->resume();
}
void GameScene::gameBack()
{
    Director::getInstance()->popScene();
}

void GameScene::update(float delta)
{
    Vec2 vec1 = gameViewLayer->convertToNodeSpace(currentBlock->getWorldSpace());
    log("node1.x:%f,node1.y%f",vec1.x,vec1.y);
}

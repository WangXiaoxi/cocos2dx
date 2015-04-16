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
#include "LBlock.h"
#include "RLBlock.h"
#include "QBlock.h"
#include "ZBlock.h"
#include "RZBlock.h"
#include "TBlock.h"
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
    fallenNodes = new Vector<BlockNode*>;
    //游戏数据初始化
    visibleSize = Director::getInstance()->getVisibleSize();
    //添加通过CocosStudio制作的游戏场景到当前Scene中
    auto rootNode = CSLoader::createNode("GameScene.csb");
    addChild(rootNode);
    
    //初始化游戏场景，获取游戏区域和下一块方块的的区域
    gameViewLayer = static_cast<Layer*>(rootNode->getChildByName("gameLayer"));
    nextBlockLayer = static_cast<Layer*>(rootNode->getChildByName("nextLayer"));
    drawGameLayerLines(gameViewLayer);
    nextBlockPosition = Vec2(nextBlockLayer->getContentSize().width/2, nextBlockLayer->getContentSize().height/2);
    bornPosition = Vec2(GAME_VIEW_WIDTH/2, GAME_VIEW_HEIGHT+NODE_HEIGHT);

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
                    {
                        if (canMoveLeft())
                        {
                            currentBlock->moveLeft();
                        }
                    }
                    break;
                case RIGHT:
                    {
                        if (canMoveRight())
                        {
                            currentBlock->moveRight();
                        }
                    }
                    break;
                case ROTATE:
                    currentBlock->setRotation90();
                    break;
                case DOWN:
                    {
                        if (canMoveDown())
                        {
                            currentBlock->moveDown();
                        }
                    }
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
    
    gameStart();
    
    return true;
}


BaseBlock * GameScene::createNewBlock(BaseBlock* oriBlock)
{
    BaseBlock*block;
    int TAG;
    int rotatedTAG;
    if (oriBlock)
    {
        TAG = oriBlock->getTag();
        rotatedTAG = oriBlock->getRotatedTAG();
    }else{
        TAG = (int)(CCRANDOM_0_1()*10)%7;
        rotatedTAG = (int)(CCRANDOM_0_1()*10)%4;
    }
    switch (TAG)
    {
        case 0:
            block = IBlock::create();
            break;
        case 1:
            block = LBlock::create();
            break;
        case 2:
            block = RLBlock::create();
            break;
        case 3:
            block = QBlock::create();
            break;
        case 4:
            block = ZBlock::create();
            break;
        case 5:
            block = RZBlock::create();
            break;
        case 6:
            block = TBlock::create();
            break;
        default:
            break;
    }
    
    for (int i = 0; i<rotatedTAG; i++)
    {
        block->setRotation90();
    }
    
    block->setTag(TAG);
    block->setRotatedTAG(rotatedTAG);
    return block;
}

void GameScene::blockCollide()
{
    if (!canMoveDown())
    {
        addNewBlock();
    }
}

bool GameScene::canMoveLeft()
{
    auto nodes = currentBlock->getNodes();
    for (auto it = nodes->begin(); it!=nodes->end(); it++)
    {
        Point position = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*it)));
        if (position.x<40)
        {
            return false;
        }
    }
    return true;
}

bool GameScene::canMoveRight()
{
    auto nodes = currentBlock->getNodes();
    for (auto it = nodes->begin(); it!=nodes->end(); it++)
    {
        Point position = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*it)));
        if (position.x>360)
        {
            return false;
        }
    }
    return true;
}

bool GameScene::canMoveDown()
{
    
    auto nodes = currentBlock->getNodes();
        for (auto it = nodes->begin(); it!=nodes->end(); it++)
        {
            Point position = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*it)));
//            log("Point.x:%f,y:%f",position.x,position.y);
            if (position.y<40)
            {
                return false;
            }
        }
    return true;
}

void GameScene::deleteCompleteLine()
{
    
}

bool GameScene::isGameOver()
{
    return true;
}

bool GameScene::isOutofGameView()
{
    auto nodes = currentBlock->getNodes();

    for (auto it=nodes->begin(); it!=nodes->end(); it++)
    {
        auto nodePosition = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*it)));
        if (nodePosition.x>400||nodePosition.x<0||nodePosition.y<0)
        {
            return true;
        }
    }

    return false;
}

void GameScene::addNewBlock()
{
    currentBlock->setBlockSchedule(BLOCK_STOP);
    
    currentBlock = createNewBlock(nextBlock);
    currentBlock->setPosition(currentBlock->getBornPosition());
    currentBlock->setScale(1);
    currentBlock->setBlockSchedule(BLOCK_SPEED);
    gameViewLayer->addChild(currentBlock);
    
    nextBlock->removeFromParent();
    nextBlock = createNewBlock(nullptr);
    nextBlock->setPosition(nextBlockPosition);
    nextBlock->setScale(0.7);
    nextBlockLayer->addChild(nextBlock);
}

void GameScene::gameStart()
{
//    log("8888888");
    nextBlock = createNewBlock(nullptr);
    nextBlock->setPosition(nextBlockPosition);
    nextBlock->setScale(0.7);
    nextBlockLayer->addChild(nextBlock);
    
    currentBlock = createNewBlock(nullptr);
    currentBlock->setPosition(currentBlock->getBornPosition());
    currentBlock->setScale(1);
    currentBlock->setBlockSchedule(BLOCK_SPEED);
    gameViewLayer->addChild(currentBlock);
}


void GameScene::gamePause()
{
    log("pause");
    Director::getInstance()->pause();
//    world->getAllBodies()
}
void GameScene::gameReStart()
{
    Director::getInstance()->resume();
}
void GameScene::gameBack()
{
    Director::getInstance()->popScene();
}

void GameScene::update(float delta)
{
//    auto nodes = currentBlock->getNodes();
//    Vec2 vec1 = gameViewLayer-> (currentBlock->getNodeWorldSpace(nodes->at(0)));
//    log("node1.x:%f,node1.y%f",vec1.x,vec1.y);
    blockCollide();
}

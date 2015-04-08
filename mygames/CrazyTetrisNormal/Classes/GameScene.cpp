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
//    world = scene->getPhysicsWorld();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GameScene::create();
    scene->addChild(layer);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    return scene;
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
    
    //初始化游戏场景，并给游戏区域添加一个等大的物理世界
    gameViewLayer = static_cast<Layer*>(rootNode->getChildByName("gameLayer"));
    nextBlockLayer = static_cast<Layer*>(rootNode->getChildByName("nextLayer"));
    auto gameViewEdge = PhysicsBody::createEdgeBox(gameViewLayer->getContentSize());
    gameViewEdge->setContactTestBitmask(CONTACT_BIT_MASK_EDGE);
//    gameViewEdge->getShape(0)->setRestitution(0.0f);
    gameViewLayer->setPhysicsBody(gameViewEdge);
    gameViewLayer->setColor(Color3B::GRAY);
    
    for (int i = 0; i<10; i++)
    {
        for (int j = 0; j<20; j++)
        {
            log("i:%d,j%D",i,j);
            Sprite *node = Sprite::create("square.png");
//            Node * node = Node::create();
            node->setTag(0);
            node->setContentSize(Size(UNIT_WIDTH, UNIT_WIDTH));
            node->setColor(Color3B::WHITE);
            node->setAnchorPoint(Vec2::ZERO);
            node->setPosition(Vec2(i*UNIT_WIDTH, j*UNIT_WIDTH));
            log("contentSize width:%f,height:%f",node->getContentSize().width,node->getContentSize().height);
            gameViewLayer->addChild(node);
        }
    }
    
    
    bornPosition = Vec2(gameViewLayer->getContentSize().width/2, gameViewLayer->getContentSize().height - UNIT_WIDTH);
    
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
                    currentBlock->moveLeft(UNIT_WIDTH);
                    break;
                case RIGHT:
                    currentBlock->moveRight(UNIT_WIDTH);
                    break;
                case ROTATE:
                    currentBlock->rotateBlock();
                    break;
                case DOWN:
                    break;
                case DOWN_IMD:
                    this->addCurrentBlock(bornPosition);
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
    
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [this](PhysicsContact & contact){
        switch (contact.getShapeA()->getContactTestBitmask()|contact.getShapeB()->getContactTestBitmask())
        {
            case CONTACT_BIT_MASK_EDGE|CONTACT_BIT_MASK_CURRENT_BLOCK:
            {
                this->currentBlock->getPhysicsBody()->setVelocity(Vec2(0, 0));
                this->addCurrentBlock(bornPosition);
                log("*************");
            }
                break;
            case CONTACT_BIT_MASK_CURRENT_BLOCK:
                this->currentBlock->getPhysicsBody()->setVelocity(Vec2(0, 0));
                this->addCurrentBlock(bornPosition);
                break;
            default:
                break;
        }
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, gameViewLayer);
    
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

void GameScene::addCurrentBlock(cocos2d::Vec2 position)
{
    currentBlock = Block::createBlock();
    currentBlock->setPosition(position);
//    currentBlock->setPosition(100, 100);
    gameViewLayer->addChild(currentBlock);
    auto body = PhysicsBody::createBox(currentBlock->getContentSize());
    body->setContactTestBitmask(CONTACT_BIT_MASK_CURRENT_BLOCK);
    body->setVelocity(Vec2(0, -100));
//    body->getShape(0)->setRestitution(0.0f);
    currentBlock->setPhysicsBody(body);
}

void GameScene::addCurrentBlock(float x, float y)
{
    currentBlock = Block::createBlock("1.png");
}

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
#include "Ranking.h"
/**************************************/

#define INIT_BUTTON(__VAR__,__ROOT__,__NAME__,__TAG__,__CLICK_CALLBACK__) \
__VAR__ = static_cast<Button*>(__ROOT__->getChildByName(__NAME__)); \
__VAR__ -> setTag(__TAG__); \
__VAR__ -> addClickEventListener(__CLICK_CALLBACK__);

#define CONTACT_BIT_MASK_EDGE           0b1000
#define CONTACT_BIT_MASK_CURRENT_BLOCK  0b0100


//#define UNIT_WIDTH Director::getInstance()->getVisibleSize().width/10
#define UNIT_WIDTH gameViewLayer->getContentSize().width/10


#define DOWN_EFFECT_FILE        "music_down.wav"  //落下音效
#define CLEAN_EFFECT_FILE "music_clean.wav" //消除音效
#define BACKGROUND_MUSIC_FILE        "music_background.mp3"  //音乐

#define ADD_SCORE_A 2   //落下一个方块2分
#define ADD_SCORE_B 10  //消除一行方块10分

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
    
    //获取系统时间
    struct timeval now;
    gettimeofday(&now, NULL);
    //初始化随机种子
    //timeval 是个结构体，里面有两个变量，一个是以秒为单位的，一个是以微秒为单位的
    unsigned rand_seed = (unsigned)(now.tv_sec*1000+now.tv_usec/1000);
    srand(rand_seed);
    
    
    
    
    
    //音效设置
    audio = SimpleAudioEngine::getInstance();
    
    audio->playBackgroundMusic(BACKGROUND_MUSIC_FILE);
    
    
    
    
    fallenNodes = new Vector<BlockNode*>;
//    fallen = new Vector<Vector<BlockNode*>*>;
   
    
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
//                    currentBlock->unscheduleUpdate();
//                    currentBlock->setBlockSchedule(BLOCK_STOP);
                    break;
                case MUSIC:
                    {
                        musicOn =! musicOn;
                        if (musicOn)
                        {
//                            audio->playBackgroundMusic(BACKGROUND_MUSIC_FILE);
                            audio->pauseBackgroundMusic();
                        }else{
//                            audio->playBackgroundMusic(BACKGROUND_MUSIC_FILE);
                            audio->resumeBackgroundMusic();
//                            audio->stopAllEffects();
//                            audio->stopBackgroundMusic();
                        }
                    }
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
    INIT_BUTTON(btnMusic, rootNode, "music", MUSIC, btnClickCallback);
    //初始化计分板
    scoreText = dynamic_cast<Text*>(rootNode->getChildByName("score"));
    updateScore(0);
//    scheduleUpdate();
    
    gameStart();
    
    return true;
}

void GameScene::updateScore(int score_i)
{
    score = score + score_i;
    auto scoreString = StringUtils::format("%d",score);
    scoreText->setString(scoreString);
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
        //停止当前大方块
        currentBlock->setBlockSchedule(BLOCK_STOP);
        //将当前大方块中节点取出，并有节点计数器记录
        auto currentNodes = currentBlock->getNodes();
        fallenNodes->pushBack(*currentNodes);
        
        for (auto it = currentNodes->begin(); it!= currentNodes->end(); it++)
        {
            BaseBlock * parent = (BaseBlock*)(*it)->getParent();
            //把小方块在父级载体中的坐标转化为相对于游戏区域内的坐标
            auto position = gameViewLayer->convertToNodeSpace(parent->getNodeWorldSpace((*it)));
            //调整小方块在游戏区域的位置
            (*it)->setPosition(position);
            //将小方块转移到游戏区
            gameViewLayer->addChild(*it);
        }
        //加两分
        updateScore(ADD_SCORE_A);
        //播放音效
        audio->playEffect(DOWN_EFFECT_FILE);
        //移除父级载体，释放资源
        currentBlock->removeFromParentAndCleanup(true);
        if (!isGameOver())
        {
            //判断消除行
            deleteCompleteLine();
            //添加新方块
            addNewBlock();
        }
    }
}

bool GameScene::canMoveLeft()
{
    auto nodes = currentBlock->getNodes();
    for (auto it = nodes->begin(); it!=nodes->end(); it++)
    {
        Point position = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*it)));
        if (position.x<NODE_WIDTH)
        {
            return false;
        }
    }
    
    auto tempNodes = currentBlock->getNodes();
    for (auto it = fallenNodes->begin(); it!= fallenNodes->end(); it++)
    {
        for (auto c_it = tempNodes->begin(); c_it!=tempNodes->end(); c_it++)
        {
            Vec2 fallenNodePosition = (*it)->getPosition();
            Vec2 currentNodePosition = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*c_it)));
            
            Rect fallenNodeBoudingBox = Rect(fallenNodePosition.x-NODE_WIDTH/2, fallenNodePosition.y-NODE_HEIGHT/2, NODE_WIDTH, NODE_HEIGHT);
            if (fallenNodeBoudingBox.containsPoint(currentNodePosition-Vec2(NODE_WIDTH, 0)))
            {
                return false;
            }
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
    
    auto tempNodes = currentBlock->getNodes();
    for (auto it = fallenNodes->begin(); it!= fallenNodes->end(); it++)
    {
        Vec2 fallenNodePosition = (*it)->getPosition();
        for (auto c_it = tempNodes->begin(); c_it!=tempNodes->end(); c_it++)
        {
            Vec2 currentNodePosition = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*c_it)));
            Rect fallenNodeBoudingBox = Rect(fallenNodePosition.x-NODE_WIDTH/2, fallenNodePosition.y-NODE_HEIGHT/2, NODE_WIDTH, NODE_HEIGHT);
            
            if (fallenNodeBoudingBox.containsPoint(currentNodePosition+Vec2(NODE_WIDTH, 0)))
            {
                return false;
            }
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
        if (position.y<40)
        {
            return false;
        }
    }
    auto tempNodes = currentBlock->getNodes();
    
    for (auto it = fallenNodes->begin(); it!= fallenNodes->end(); it++)
    {

        for (auto c_it = tempNodes->begin(); c_it!=tempNodes->end(); c_it++)
        {
            Vec2 fallenNodePosition = (*it)->getPosition();
            Vec2 currentNodePosition = gameViewLayer->convertToNodeSpace(currentBlock->getNodeWorldSpace((*c_it)));
            if (fabs(currentNodePosition.x-fallenNodePosition.x)>20)
            {
                continue;
            }
            
            if ((currentNodePosition.y-fallenNodePosition.y)<60)
            {
                return false;
            }
            
        }
    }
    return true;
}

void GameScene::deleteCompleteLine()
{
    //lines为屏幕中行数，共20行，这里初始化行数
    for (int i=0; i<20; i++)
    {
        lines[i] = new Vector<BlockNode*>;
    }
    
    //遍历所有已落下方块，根据坐标计算所在行，并添加至行数计数器lines中
    for (auto it = fallenNodes->begin(); it!=fallenNodes->end();it++)
    {
        //获取方块节点的y轴坐标 注：这里貌似是cocos2d-x的bug，若直接计算则会出现错误。
        int y = (*it)->getPosition().y+0.5;
        //单元格高度
        int height =  NODE_HEIGHT;
        //得到行数
        int line = y/height;
        //添加至行数计数器
        lines[line]->pushBack((*it));
    }
    
    //判断每一行是否填满了小方块
    for (int i = 0; i < 20; i++)
    {
        log("line[%d].count:%zd",i,lines[i]->size());
        //每行最多容纳10个小方块，装满则消除
        if (lines[i]->size()>9)
        {
            //播放消除音效
            audio->playEffect(CLEAN_EFFECT_FILE);
            //对本行方块逐个消除
            for (auto it = lines[i]->begin(); it!=lines[i]->end(); it++)
            {
                //从当前屏幕中移除，且移出方块计数器
                gameViewLayer->removeChild(*it);
                fallenNodes->eraseObject(*it);
            }
            //消除一次加十分
            updateScore(ADD_SCORE_B);
            //释放消除方块资源
            lines[i]->clear();
            //将消除行以上的方块全部向下移动
            for (int j=19; j>i; j--)
            {
                for (auto itt = lines[j]->begin(); itt!=lines[j]->end(); itt++)
                {
                    (*itt)->moveDown();
                }
            }
        }
        //释放当前行数计数器资源
        lines[i]->clear();
    }
    
}

bool UDgreater ( int elem1, int elem2 )
{
    return elem1 > elem2;
}

bool GameScene::isGameOver()
{
    //如果已落下的方块中，y轴坐标超出了游戏区域，则游戏结束
    for (auto it = fallenNodes->begin(); it!=fallenNodes->end(); it++)
    {
        if (((*it)->getPosition().y - GAME_VIEW_HEIGHT)>0.0)
        {
            log("Game Over!");
            //取消定时器
            unscheduleUpdate();
            Layer * layer = Layer::create();
            layer->setContentSize(Director::getInstance()->getWinSize());
            std::string name = "game_over.jpg";
            Sprite * over = Sprite::create(name);
            over->setPosition(layer->getContentSize()/2);
            over->setScale(0.35);
            layer->addChild(over);
            addChild(layer);
            
            auto listener = EventListenerTouchOneByOne::create();
            listener->onTouchBegan = [](Touch*t,Event*e){
                Director::getInstance()->popScene();
                return false;};
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, over);
            
            
            //保存分数
            
            auto ranking = Ranking::getRankingData();
            
            int arr[9];
            for (int i=0; i<8; i++)
            {
                arr[i]=ranking.at(i).asInt();
            }
            ranking.clear();
            arr[8]=score;
            
            for(int i = 0;i < 9;i++){
                //比较两个相邻的元素
                for(int j = 0;j < 9-i-1;j++){
                    if(arr[j] < arr[j+1]){
                        int t = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = t;
                    }  
                }  
            }
            
            
            for (int i = 0; i<8; i++)
            {
                ranking.push_back(Value(arr[i]));
            }
            
            Ranking::updateRankingData(ranking);
            
            return true;
        }
    }
    return false;
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
    scheduleUpdate();
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
    unscheduleUpdate();
    currentBlock->setBlockSchedule(BLOCK_STOP);

//    Director::getInstance()->pause();
//    world->getAllBodies()
}
void GameScene::gameReStart()
{
    scheduleUpdate();
    currentBlock->setBlockSchedule(BLOCK_SPEED);
}
void GameScene::gameBack()
{
    //停止背景音乐的播放
    audio->stopBackgroundMusic();
    //停止所有音效
    audio->stopAllEffects();
    //弹出当前游戏场景
    Director::getInstance()->popScene();
}

void GameScene::update(float delta)
{
    blockCollide();
}

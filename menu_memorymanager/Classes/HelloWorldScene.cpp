#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    TableView *tb = TableView::create(this, Size(300, 300));
//    auto *tb = TableView::create(this, Size(300,300));
//    tb->setAnchorPoint(Vec2(0, 0));
    tb->setPosition(visibleSize.width/2, visibleSize.height/2);
    tb->setDelegate(this);
//    addChild(tb);
//    auto sprite = Sprite::create("HelloWorld.png");
//    sprite->autorelease();
    this->addChild(tb);
    return true;
}

Size HelloWorld::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return Size(300,50);
}

TableViewCell* HelloWorld::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    TableViewCell *cell = table->dequeueCell();
    Label *label;
    if (cell == nullptr) {
        cell = TableViewCell::create();
        label = Label::create();
        label->setTag(2);
        label->setAnchorPoint(Vec2(0, 0));
        label->setSystemFontSize(50);
        cell->addChild(label);
    }else{
        label = (Label* )cell->getChildByTag(2);
    }
    label->setString(StringUtils::format("label %ld",idx));
    return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 100;
}

void HelloWorld::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    Label* label = (Label*)cell->getChildByTag(2);
    log("%s--is touched",label->getString().c_str());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

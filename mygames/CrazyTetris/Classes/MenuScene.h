//
//  MenuScene.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/3/5.
//
//

#ifndef __CrazyTetris__MenuScene__
#define __CrazyTetris__MenuScene__

#include <cocos2d.h>

USING_NS_CC;

class MenuScene : public Layer{

public:
    
    enum ClickTag
    {
        START_GAME,
        EXIT_GAME
    };
    
    static Scene * createScene();
    
    virtual bool init();
    
    CREATE_FUNC(MenuScene);
    
    static void clickCallback(Ref * ref);
};


#endif /* defined(__CrazyTetris__MenuScene__) */

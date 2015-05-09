//
//  HeroListScene.h
//  CrazyTetris
//
//  Created by wangxi on 15/4/29.
//
//

#ifndef __CrazyTetris__HeroListScene__
#define __CrazyTetris__HeroListScene__

#include <cocos2d.h>
#include "Ranking.h"

USING_NS_CC;

class HeroListScene : public Layer {
    

public:
    
    static Scene * createScene();
    CREATE_FUNC(HeroListScene);
    
    virtual bool init();
    
};

#endif /* defined(__CrazyTetris__HeroListScene__) */

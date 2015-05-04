//
//  ServerSelect.h
//  CrazyTetris
//
//  Created by wangxi on 15/4/30.
//
//

#ifndef __CrazyTetris__ServerSelect__
#define __CrazyTetris__ServerSelect__

#include <stdio.h>
#include <cocos2d.h>
#include <CocosGUI.h>
#include <cocostudio/CocoStudio.h>

USING_NS_CC;

class ServerSelect : public Layer
{
public:
    static Scene * createScene();
    virtual bool init();
    CREATE_FUNC(ServerSelect);
    
};

#endif /* defined(__CrazyTetris__ServerSelect__) */

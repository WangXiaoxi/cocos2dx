//
//  Ball.h
//  Lesson6_CustomClass
//
//  Created by wangxi on 14-7-5.
//
//

#ifndef __Lesson6_CustomClass__Ball__
#define __Lesson6_CustomClass__Ball__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class Ball:public Sprite {
    
public:
    virtual bool init();
    CREATE_FUNC(Ball);
};


#endif /* defined(__Lesson6_CustomClass__Ball__) */

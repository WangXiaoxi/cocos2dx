//
//  ImageScene.h
//  L01StartScene
//
//  Created by nyist-mac1 on 15/4/3.
//
//

#ifndef __L01StartScene__ImageScene__
#define __L01StartScene__ImageScene__

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;

class ImageScene : public Layer {
    
public:
    
    static Scene * createScene();
    
    virtual bool init();
    
    CREATE_FUNC(ImageScene);
    
private:
    Size visibleSize;
};

#endif /* defined(__L01StartScene__ImageScene__) */

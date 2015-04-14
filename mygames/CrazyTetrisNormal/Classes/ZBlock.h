//
//  ZBlock.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#ifndef __CrazyTetris__ZBlock__
#define __CrazyTetris__ZBlock__
//Z型方块
#include <stdio.h>
#include "BaseBlock.h"

class ZBlock : public BaseBlock
{
    
public:
    bool init();
    CREATE_FUNC(ZBlock);
    Point getBornPosition();
    void setRotation90();
};

#endif /* defined(__CrazyTetris__ZBlock__) */

//
//  LBlock.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#ifndef __CrazyTetris__LBlock__
#define __CrazyTetris__LBlock__
//L型方块
#include <stdio.h>
#include "BaseBlock.h"

class LBlock : public BaseBlock
{
public:
    virtual bool init();
    CREATE_FUNC(LBlock);
    Point getBornPosition();
};

#endif /* defined(__CrazyTetris__LBlock__) */

//
//  IBlock.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#ifndef __CrazyTetris__IBlock__
#define __CrazyTetris__IBlock__
//I型方块，| -- 直线型
#include <stdio.h>
#include "BaseBlock.h"


class IBlock : public BaseBlock
{

public:
    virtual bool init();
    CREATE_FUNC(IBlock);
    Vec2 getBornPosition();
    void setRotation90();
};

#endif /* defined(__CrazyTetris__IBlock__) */

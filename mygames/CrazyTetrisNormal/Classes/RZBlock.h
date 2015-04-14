//
//  RZBlock.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#ifndef __CrazyTetris__RZBlock__
#define __CrazyTetris__RZBlock__
//反Z型方块
#include <stdio.h>
#include "BaseBlock.h"

class RZBlock : public BaseBlock
{

public:
    bool init();
    CREATE_FUNC(RZBlock);
    Point getBornPosition();
    void setRotation90();
};
#endif /* defined(__CrazyTetris__RZBlock__) */

//
//  RLBlock.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#ifndef __CrazyTetris__RLBlock__
#define __CrazyTetris__RLBlock__
//反L型方块
#include <stdio.h>
#include "BaseBlock.h"

class RLBlock : public BaseBlock
{
    
public:
    bool init();
    CREATE_FUNC(RLBlock);
    Point getBornPosition();
};

#endif /* defined(__CrazyTetris__RLBlock__) */

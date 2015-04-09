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
#include "Block.h"

class IBlock : public Block
{
    
public:
    CREATE_FUNC(IBlock);
};

#endif /* defined(__CrazyTetris__IBlock__) */

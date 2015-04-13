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
    BlockNode * blockNode1;
    virtual bool init();
    virtual Point getWorldSpace(BlockNode*);
    void setRotation90();
    CREATE_FUNC(IBlock);
};

#endif /* defined(__CrazyTetris__IBlock__) */

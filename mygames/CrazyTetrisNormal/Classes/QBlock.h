//
//  QBlock.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#ifndef __CrazyTetris__QBlock__
#define __CrazyTetris__QBlock__
//田字形，正方形方块
#include <stdio.h>
#include "BaseBlock.h"

class QBlock : public BaseBlock
{
    
public:
    virtual bool init();
    CREATE_FUNC(QBlock);
    Point getBornPosition();
};

#endif /* defined(__CrazyTetris__QBlock__) */

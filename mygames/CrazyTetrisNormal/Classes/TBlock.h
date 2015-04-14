//
//  TBlock.h
//  CrazyTetris
//
//  Created by nyist-mac1 on 15/4/8.
//
//

#ifndef __CrazyTetris__TBlock__
#define __CrazyTetris__TBlock__
//T型方块
#include <stdio.h>
#include "BaseBlock.h"

class TBlock : public BaseBlock
{
    
public:
    bool init();
    CREATE_FUNC(TBlock);
    virtual Vec2 getBornPosition();
};
#endif /* defined(__CrazyTetris__TBlock__) */

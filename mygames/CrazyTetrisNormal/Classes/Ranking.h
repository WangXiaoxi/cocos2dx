//
//  Ranking.h
//  CrazyTetris
//
//  Created by wangxi on 15/5/10.
//
//

#ifndef __CrazyTetris__Ranking__
#define __CrazyTetris__Ranking__

#include <stdio.h>
#include <cocos2d.h>

USING_NS_CC;



class Ranking :public Layer
{

public:
    
    static ValueVector getRankingData();
    static void updateRankingData(ValueVector);
};

#endif /* defined(__CrazyTetris__Ranking__) */

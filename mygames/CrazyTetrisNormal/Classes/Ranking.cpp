//
//  Ranking.cpp
//  CrazyTetris
//
//  Created by wangxi on 15/5/10.
//
//

#include "Ranking.h"
ValueVector Ranking::getRankingData()
{
    ValueVector ranking;
    
    for (int i = 0; i < 8; i++)
    {
        auto scoreStr = StringUtils::format("score%d",i).c_str();
        int score = UserDefault::getInstance()->getIntegerForKey(scoreStr, 0);
        ranking.push_back(Value(score));
    }
    return ranking;
}

void Ranking::updateRankingData(ValueVector ranking)
{
    //若为空则停止运行
    if (!ranking.size())
    {
        return;
    }
    
    for (int i = 0; i < 8; i++)
    {
        auto scoreStr = StringUtils::format("score%d",i).c_str();
        UserDefault::getInstance()->setIntegerForKey(scoreStr, ranking.at(i).asInt());
    }
    //刷新数据
    UserDefault::getInstance()->flush();
}
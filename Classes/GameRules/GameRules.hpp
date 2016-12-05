//
//  GameRules.hpp
//  Candy
//
//  Created by JustinYang on 16/12/3.
//
//

#ifndef GameRules_hpp
#define GameRules_hpp

#include <stdio.h>
#include "ChessControl.hpp"

class GameRules
{
public:
    static GameRules *getInstance();
    
    void setConfig();
    
    bool checkOut(ChessPoint point);//检测点是否满足棋盘内
    bool checkColor(int color);//检测颜色时候是满足设定
    
    void checkToClean(ChessPoint point,VecChessFather &pVector);//将可以消除的点填入数组
    
    void cleanSelect();//清楚收集点
    
    void vertialFall(VecChessFather &pVector);//竖直下落检查
    
    void horizontalMove(VecChessFather &pVector);//横向移动检查
    
    bool overCheck(VecChessFather &pVector);//失败检查
    
    void endGameCheck(VecChessFather &pVector);//本局游戏结束。发放奖励
    
    void rearrangeChess(VecChessFather &pVector);//重新排列道具
    

private:
    //获取
    ChessFather *getObject(ChessPoint point);
    //消除选择
    void checkNext(ChessPoint point,int nColor);
    void checkSelect(ChessPoint point);//收集所触摸点的相连点
    //竖直下落
    void vertialFallAtY(ChessFather *pNode,VecChessFather &pVector);
    //横向移动
    void horizontalMoveAtY(ChessFather *pNode,VecChessFather &pVector);
    void horizontalMoveAtX(ChessFather *pNode,VecChessFather &pVector);
    //结束检查
    bool checkOver(ChessPoint point,int nColor,VecChessFather &pVector);
    bool checkOverNext(ChessPoint point,int nColor,VecChessFather &pVector);
    
private:
    ~GameRules();
private:
    
    VecChessFather              m_ChessSelect;
    int                         m_CheckBest;
    
    int                         m_nMaxX;
    int                         m_nMaxY;
};

#endif /* GameRules_hpp */

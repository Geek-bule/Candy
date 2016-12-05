//
//  GameRules.cpp
//  Candy
//
//  Created by JustinYang on 16/12/3.
//
//

#include "GameRules.hpp"


static GameRules *instance = nullptr;

GameRules *GameRules::getInstance()
{
    if (instance == nullptr) {
        instance = new GameRules();
    }
    return instance;
}

void GameRules::setConfig()
{
    m_nMaxX = ChessControl::getInstance()->getMaxX();
    m_nMaxY = ChessControl::getInstance()->getMaxY();
}

GameRules::~GameRules()
{
    
}

//
////
//

ChessFather *GameRules::getObject(ChessPoint point)
{
    return ChessControl::getInstance()->selectChess(point);
}


bool GameRules::checkOut(ChessPoint point)
{
    if (point.x < 0|| point.x >= m_nMaxX || point.y < 0 || point.y >= m_nMaxY) {
        return true;
    }
    return false;
}

bool GameRules::checkColor(int color)
{
    if (color <= CHESS_COLOR_NONE || color >= CHESS_COLOR_MAX) {
        return true;
    }
    return false;
}

void GameRules::checkToClean(ChessPoint point,VecChessFather &pVector)
{
    
    //check select
    checkSelect(point);
    if (m_ChessSelect.size() >= 2) {
//        APSound::getInstance()->playEffect("music/selectboy.mp3");
        for (int index = 0; index < m_ChessSelect.size(); index ++){
            ChessFather *pNode = m_ChessSelect.at(index);
            pNode->setChessSelected(true);
            pVector.push_back(pNode);
        }
    }else if (m_ChessSelect.size() == 1){
        ChessFather *pNode = m_ChessSelect.at(0);
        pNode->setChessSelected(false);
    }
    
    m_ChessSelect.clear();
}

void GameRules::checkNext(ChessPoint point,int color)
{
    if (checkOut(point)) {
        return;
    }
    ChessFather *pNode = getObject(point);
    if (pNode->getChessColor() == color && !pNode->getChessSelected()){
        checkSelect(point);
    }
}

void GameRules::checkSelect(ChessPoint point)
{
    if (checkOut(point)) {
        return;
    }
    ChessFather *pNode = getObject(point);
    if (checkColor(pNode->getChessColor())) {
        return;
    }
    pNode->setChessSelected(true);
    m_ChessSelect.push_back(pNode);
    
    //上下左右
    checkNext(ChessPoint(point.x,point.y+1), pNode->getChessColor());
    checkNext(ChessPoint(point.x,point.y-1), pNode->getChessColor());
    checkNext(ChessPoint(point.x-1,point.y), pNode->getChessColor());
    checkNext(ChessPoint(point.x+1,point.y), pNode->getChessColor());
}



void GameRules::cleanSelect()
{
    for (int index = 0; index < m_ChessSelect.size(); index++) {
        ChessFather *pNode = m_ChessSelect.at(index);
        //释放颜色
        pNode->setChessColor(0);
    }
}

void GameRules::vertialFall(VecChessFather &pVector)
{
    
    for (int y =0; y < m_nMaxY; y++) {
        for (int x = 0; x < m_nMaxX; x++) {//

            ChessFather *pNode = getObject(ChessPoint(x, y));
            if (pNode->getChessColor() == 0) {
                vertialFallAtY(pNode,pVector);
            }
        }
    }
}

void GameRules::vertialFallAtY(ChessFather* pNode,VecChessFather &pVector)
{
    for (int y = pNode->getChessPotY(); y < m_nMaxY; y++) {
        ChessFather *pCheck = getObject(ChessPoint(pNode->getChessPotX(), y));
        if (pCheck->getChessColor() > CHESS_COLOR_NONE && pCheck->getChessColor() < CHESS_COLOR_MAX) {
            //交换2个元素
            ChessControl::getInstance()->swapChess(pCheck, pNode);
            pVector.push_back(pNode);
            return;
        }
    }
}


void GameRules::horizontalMove(VecChessFather &pVector)
{
    for (int x = 0; x < m_nMaxX; x++) {
        ChessFather* pNode = getObject(ChessPoint(x, 0));
        if (pNode->getChessColor() == 0) {
            horizontalMoveAtX(pNode, pVector);
        }
    }
}

void GameRules::horizontalMoveAtX(ChessFather *pNode,VecChessFather &pVector)
{
    int pox = -1;
    //寻找可以左移动的行
    for (int x = pNode->getChessPotX(); x < m_nMaxX; x++) {
        ChessFather *pCheck = getObject(ChessPoint(x, pNode->getChessPotY()));
        if (pCheck->getChessColor() > CHESS_COLOR_NONE && pCheck->getChessColor() < CHESS_COLOR_MAX) {
            pox = x;
            break;
        }
    }
    //如果没有找到，返回
    if (pox == -1) {
        return;
    }
    
    //对找到的行进行交换
    for (int y = 0; y < m_nMaxY; y++) {
        ChessFather *pCheck = getObject(ChessPoint(pox, y));
        ChessFather *pSwap = getObject(ChessPoint(pNode->getChessPotX(), y));
        if (pCheck->getChessColor() > CHESS_COLOR_NONE && pCheck->getChessColor() < CHESS_COLOR_MAX) {
            //交换2个元素
            ChessControl::getInstance()->swapChess(pCheck, pNode);
            pVector.push_back(pSwap);
        }
    }
}

bool GameRules::overCheck(VecChessFather &pVector)
{
    bool isOver = true;
    m_CheckBest = 0;
    int nTotle = 0;
    for (int y =0; y < m_nMaxY; y++) {
        for (int x = 0; x < m_nMaxX; x++) {
            if ((x%2 == 0 && y%2 == 0) || (x%2 != 0 && y%2 != 0)) {
                ChessFather *pNode = getObject(ChessPoint(x, y));
                if (pNode->getChessColor() > CHESS_COLOR_NONE && pNode->getChessColor() < CHESS_COLOR_MAX) {
                    if (checkOver(pNode->getChessPoint(), pNode->getChessColor(), pVector)){
                        isOver = false;
                        nTotle++;
                    }
                }
            }
        }
    }

    return isOver;
}

bool GameRules::checkOver(ChessPoint point,int nColor,VecChessFather &pVector)
{
    bool isCheck = false;
    if (checkOverNext(ChessPoint(point.x+0, point.y+1), nColor, pVector)) {
        isCheck = true;
    }
    if (checkOverNext(ChessPoint(point.x+0, point.y-1), nColor, pVector)) {
        isCheck = true;
    }
    if (checkOverNext(ChessPoint(point.x-1, point.y+0), nColor, pVector)) {
        isCheck = true;
    }
    if (checkOverNext(ChessPoint(point.x+1, point.y+0), nColor, pVector)) {
        isCheck = true;
    }
    return isCheck;
}

bool GameRules::checkOverNext(ChessPoint point, int color,VecChessFather &pVector)
{
    if (checkOut(point)) {
        return false;
    }
    ChessFather *pNode = getObject(point);
    if (pNode->getChessColor() == color){
        //寻找最优解
        checkSelect(point);
        for (int index = 0; index < m_ChessSelect.size(); index++) {
            ChessFather *pNode = m_ChessSelect.at(index);
            pNode->setChessSelected(false);
        }
        if (m_ChessSelect.size() > m_CheckBest) {
            m_CheckBest = m_ChessSelect.size();
            pVector.clear();
            for (int index=0 ; index < m_ChessSelect.size(); index++) {
                pVector.push_back(m_ChessSelect.at(index));
            }
        }
        m_ChessSelect.clear();
        return true;
    }
    return false;
}

void GameRules::endGameCheck(VecChessFather &pVector)
{
    //将剩余的元素全部添加到数组中,数据清空，奖励分数
    for (int y =m_nMaxY-1; y >= 0; y--) {
        for (int x = y%2==0? m_nMaxY-1:0; y%2==0? x>=0:x < m_nMaxX; y%2==0? x--:x++) {
            ChessFather *pNode = getObject(ChessPoint(x, y));
            if (pNode->getChessColor() != 0) {
                //这个位置时直接清零还是随机下一关呢？
                pNode->setChessColor(0);
                pVector.push_back(pNode);
            }
        }
    }
}

void GameRules::rearrangeChess(VecChessFather &pVector)
{
    //收集到数组
    for (int y =0; y < m_nMaxY; y++) {
        for (int x = 0; x < m_nMaxX; x++) {
            ChessFather *pNode = getObject(ChessPoint(x, y));
            if (pNode->getChessColor() != 0) {
                m_ChessSelect.push_back(pNode);
            }
        }
    }
    
    //重新排列
    int size = (int)m_ChessSelect.size();
    for (int i = 0; i < size/2; i++) {
        ChessFather* pNode = m_ChessSelect.at(0);
        int index = rand()%(m_ChessSelect.size()-1)+1;
        ChessFather* pSwap = m_ChessSelect.at(index);
        ChessControl::getInstance()->swapChess(pNode, pSwap);
        m_ChessSelect.erase(m_ChessSelect.begin());
        m_ChessSelect.erase(m_ChessSelect.begin() + index - 1);
    }
    
    if (overCheck(pVector)){
        rearrangeChess(pVector);
        return;
    }//如果出现死局，要重新排列
    
    //收集到数组
    for (int y =0; y < m_nMaxY; y++) {
        for (int x = 0; x < m_nMaxX; x++) {
            ChessFather *pNode = getObject(ChessPoint(x, y));
            if (pNode->getChessColor() != 0) {
                pVector.push_back(pNode);
            }
        }
    }
    
    //清空
    m_ChessSelect.clear();
}





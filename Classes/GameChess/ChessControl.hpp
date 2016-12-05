//
//  ChessControl.hpp
//  Candy
//
//  Created by JustinYang on 16/12/3.
//
//

#ifndef ChessControl_hpp
#define ChessControl_hpp

#include <stdio.h>
#include "ChessBasic.hpp"


typedef std::vector<ChessFather*> VecChessFather;


//chess create with type
ChessFather *createChess(CHESS_TYPE type) {
    ChessFather* pChess = nullptr;
    switch (type) {
        case CHESS_TYPE_NONE:
            
            break;
        case CHESS_TYPE_BASIC:
            pChess = ChessBasic::createChess();
            break;
        default:
            break;
    }
    return pChess;
}



class ChessControl
{
public:
    //instance
    static ChessControl* getInstance();
    
    //insert
    void insertChess(CHESS_POT potX, CHESS_POT potY, ChessFather *pChess);
    void insertChess(CHESS_POT potX, CHESS_POT potY, CHESS_TYPE type);
    void insertChess(ChessPoint point, ChessFather *pChess);
    void insertChess(ChessPoint point, CHESS_TYPE type);
    //update
    void updateChess(CHESS_POT potX, CHESS_POT potY, ChessFather *pChess);
    void updateChess(CHESS_POT potX, CHESS_POT potY, CHESS_TYPE type);
    void updateChess(ChessPoint point, ChessFather *pChess);
    void updateChess(ChessPoint point, CHESS_TYPE type);
    //delete
    void deleteChess(ChessFather *pChess);
    void deleteChess(CHESS_POT potX, CHESS_POT potY);
    void deleteChess(ChessPoint point);
    //select
    ChessFather* selectChess(CHESS_POT potX, CHESS_POT potY);
    ChessFather* selectChess(ChessPoint point);
    ChessPoint selectChess(ChessFather *pChess);
    //swap
    void swapChess(CHESS_POT startX, CHESS_POT startY,CHESS_POT endX, CHESS_POT endY);
    void swapChess(ChessPoint start, ChessPoint end);
    void swapChess(ChessFather *pStart, ChessFather *pEnd);
    
public:
    //get
    int         getMaxX();
    int         getMaxY();
    
    
    //set
    void        setMaxX(int nX);
    void        setMaxY(int nY);
private:
    ChessControl();
    ~ChessControl();
private:
    VecChessFather              m_vecChess;
    int                         m_nMaxX;
    int                         m_nMaxY;
};




#endif /* ChessControl_hpp */

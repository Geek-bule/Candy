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
    static ChessControl* getInstance();
    
    //insert
    void insertChess(CHESS_POT potX, CHESS_POT potY, CHESS_TYPE type);
    void insertChess(ChessPoint point, CHESS_TYPE type);
    //update
    void updateChess(CHESS_POT potX, CHESS_POT potY, CHESS_TYPE type);
    void updateChess(ChessPoint point, CHESS_TYPE type);
    //delete
    void deleteChess(CHESS_POT potX, CHESS_POT potY);
    void deleteChess(ChessPoint point);
    //select
    ChessFather* selectChess(CHESS_POT potX, CHESS_POT potY);
    ChessFather* selectChess(ChessPoint point);
    //swap
    void swapChess(CHESS_POT startX, CHESS_POT startY,CHESS_POT endX, CHESS_POT endY);
    void swapChess(ChessPoint start, ChessPoint end);
    
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
    std::vector<ChessFather*>   m_vecChess;
    int                         m_nMaxX;
    int                         m_nMaxY;
};




#endif /* ChessControl_hpp */

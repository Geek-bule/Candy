//
//  ChessFather.hpp
//  Candy
//
//  Created by JustinYang on 16/12/3.
//
//

#ifndef ChessFather_hpp
#define ChessFather_hpp

#include <stdio.h>
#include "chessConfig.h"
#include "ChessPoint.h"

class ChessFather
{
public:
    
    
public:
    //get
    CHESS_TYPE      getChessType(){return m_nChessType;}
    CHESS_COLOR     getChessColor(){return m_nCHessColor;}
    CHESS_POT       getChessPotX(){return m_nChessPotX;}
    CHESS_POT       getChessPotY(){return m_nChessPotY;}
    ChessPoint      getChessPoint(){return ChessPoint(m_nChessPotX, m_nChessPotY);}
    bool            getChessSelected(){return m_bChessSelected;}
    
    //set
    void            setChessColor(CHESS_COLOR color);
    void            setChessPotX(CHESS_POT potX);
    void            setChessPotY(CHESS_POT potY);
    void            setChessPoint(ChessPoint pot);
    void            setChessSelected(bool status);
protected:
    void            setChessType(CHESS_TYPE type);
private:
    //basic property
    CHESS_TYPE      m_nChessType;
    CHESS_COLOR     m_nCHessColor;
    CHESS_POT       m_nChessPotX;
    CHESS_POT       m_nChessPotY;
    
    //popstar property
    bool            m_bChessSelected;
};

#endif /* ChessFather_hpp */

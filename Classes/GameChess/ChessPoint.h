//
//  ChessPoint.hpp
//  Candy
//
//  Created by JustinYang on 16/12/3.
//
//

#ifndef ChessPoint_hpp
#define ChessPoint_hpp

#include <stdio.h>

class ChessPoint
{
public:
    int x;
    int y;
    
    ChessPoint();
    ChessPoint(int x,int y);
};


inline ChessPoint::ChessPoint()
: x(0),y(0)
{
    
}

inline ChessPoint::ChessPoint(int xx,int yy)
:x(xx),y(yy)
{
    
}

#endif /* ChessPoint_hpp */

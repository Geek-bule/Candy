//
//  ChessBasic.hpp
//  Candy
//
//  Created by JustinYang on 16/12/3.
//
//

#ifndef ChessBasic_hpp
#define ChessBasic_hpp

#include <stdio.h>
#include "ChessFather.hpp"

class ChessBasic : public ChessFather
{
public:
    static ChessBasic *createChess();
private:
    ChessBasic();
    ~ChessBasic();
    bool init();
};
#endif /* ChessBasic_hpp */

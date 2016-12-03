//
//  chessConfig.h
//  Candy
//
//  Created by JustinYang on 16/12/3.
//
//

#ifndef chessConfig_h
#define chessConfig_h


//type
typedef int CHESS_TYPE;

#define CHESS_TYPE_NONE                     0
#define CHESS_TYPE_BASIC                    1

//color
typedef int CHESS_COLOR;

#define CHESS_COLOR_NONE                    0
#define CHESS_COLOR_RED                     1
#define CHESS_COLOR_BLUE                    2
#define CHESS_COLOR_GREEN                   3
#define CHESS_COLOR_YELLOW                  4
#define CHESS_COLOR_PURPLE                  5
#define CHESS_COLOR_MAX                     6


typedef int CHESS_POT;
struct  CHESS_POINT
{
    CHESS_POT   nX;
    CHESS_POT   nY;
};



#endif /* chessConfig_h */

//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "ChessPiece.h"

class Queen : ChessPiece {
public:
    bool canMove(Coordinates coordinates);
};


#endif //CHESS_QUEEN_H

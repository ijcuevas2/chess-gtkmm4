//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H
#include "ChessPiece.h"

class King : ChessPiece {
public:
    bool canMove(Coordinates coordinates);
};


#endif //CHESS_KING_H

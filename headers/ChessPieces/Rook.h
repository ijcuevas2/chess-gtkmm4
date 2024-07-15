//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "ChessPiece.h"

class Rook : ChessPiece {
public:
    bool canMove(Coordinates coordinates);
};


#endif //CHESS_ROOK_H

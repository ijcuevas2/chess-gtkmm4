//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "ChessPiece.h"

class Knight : ChessPiece {
public:
    bool canMove(Coordinates coordinates);
};


#endif //CHESS_KNIGHT_H

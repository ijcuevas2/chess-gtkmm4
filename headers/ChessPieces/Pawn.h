//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "ChessPiece.h"

class Pawn : ChessPiece {
public:
    bool canMove(Coordinates coordinates) {
      return true;
    }
};


#endif //CHESS_PAWN_H

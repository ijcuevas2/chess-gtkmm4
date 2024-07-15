//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_EMPTYPIECE_H
#define CHESS_EMPTYPIECE_H
#include "ChessPiece.h"

class EmptyPiece : ChessPiece {
public:
    bool canMove(Coordinates coordinates);
};


#endif //CHESS_EMPTYPIECE_H

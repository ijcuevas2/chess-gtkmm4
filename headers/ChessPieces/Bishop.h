//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "ChessPiece.h"

class Bishop : ChessPiece {
public:
    bool canMove(Coordinates coordinates);
    void afterPieceMoved(Coordinates coordinates) override;
};


#endif //CHESS_BISHOP_H

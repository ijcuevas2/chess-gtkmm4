//
// Created by Ismael Cuevas on 7/31/24.
//

#ifndef CHESS_MATHUTILS_H
#define CHESS_MATHUTILS_H


#include "Coordinates/Coordinates.h"

class MathUtils {
public:
    static int getNextCoordinate(int source, int dest);
    static bool isSourceEqualToTarget(Coordinates coordinates);
    static Coordinates getNewDiagonalCoordinates(Coordinates coordinates);
    static Coordinates getNewHorizontalCoordinates(Coordinates coordinates);
    static bool isPositive(int num);
    static bool isPositiveVerticalDirection(Coordinates coordinates);
};


#endif //CHESS_MATHUTILS_H

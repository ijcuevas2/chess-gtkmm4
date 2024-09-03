//
// Created by Ismael Cuevas on 7/31/24.
//

#ifndef CHESS_MATHUTILS_H
#define CHESS_MATHUTILS_H


#include "Point2DPair/Point2DPair.h"
#include <iostream>

class MathUtils {
public:
    static int getNextCoordinate(int source, int dest);
    static bool isSourceEqualToTarget(Point2DPair point2dPair);
    static Point2DPair getNewDiagonalCoordinates(Point2DPair point2dPair);
    static Point2DPair getNewHorizontalCoordinates(Point2DPair point2dPair);
    static bool isPositive(int num);
    static bool isPositiveVerticalDirection(Point2DPair point2dPair);
    static int charToDigit(char c);
};


#endif //CHESS_MATHUTILS_H

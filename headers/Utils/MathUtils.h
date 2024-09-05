//
// Created by Ismael Cuevas on 7/31/24.
//

#ifndef CHESS_MATHUTILS_H
#define CHESS_MATHUTILS_H


#include "Point2DPair/Point2DPair.h"
#include "Point2D/Point2D.h"
#include <iostream>
#include <vector>

class MathUtils {
public:
    static int getNextCoordinate(int source, int dest);
    static bool isSourceEqualToTarget(Point2DPair point2dPair);
    static Point2DPair getNewDiagonalCoordinates(Point2DPair point2dPair);
    static Point2DPair getNewHorizontalCoordinates(Point2DPair point2dPair);
    static bool isPositive(int num);
    static bool isPositiveVerticalDirection(Point2DPair point2dPair);
    static int charToDigit(char c);
    static bool isValidPoint2D(Point2D point2D);
    static std::vector<Point2D> getAdjacentKingPoints(Point2D point2D);
};

#endif //CHESS_MATHUTILS_H

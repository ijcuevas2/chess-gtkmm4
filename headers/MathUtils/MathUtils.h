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
private:
    static int isPositive(int num);
};


#endif //CHESS_MATHUTILS_H

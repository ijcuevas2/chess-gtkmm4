//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_POINT2DPAIR_H
#define CHESS_POINT2DPAIR_H

class Point2DPair {
private:
    int _srcRow;
    int _srcCol;
    int _tgtRow;
    int _tgtCol;

public:
    explicit Point2DPair();
    explicit Point2DPair(int srcRow, int srcCol, int tgtRow, int tgtCol);

    int getSrcRow() const;
    int getSrcCol() const;
    int getTgtRow() const;
    int getTgtCol() const;
};


#endif //CHESS_POINT2DPAIR_H

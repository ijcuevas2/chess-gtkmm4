//
// Created by Ismael Cuevas on 8/9/24.
//

#ifndef CHESS_POINT2D_H
#define CHESS_POINT2D_H


class Point2D {
private:
    int row;
    int col;
public:
    Point2D();
    Point2D(int row, int col);
    int getRow();
    int getCol();
    void setRow(int row);
    void setCol(int col);
    bool operator==(const Point2D & other) const;
};

#endif //CHESS_POINT2D_H

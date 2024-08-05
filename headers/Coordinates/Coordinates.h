//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_COORDINATES_H
#define CHESS_COORDINATES_H

class SinglePieceCoordinates {
private:
    int row;
    int col;
public:
    SinglePieceCoordinates();
    SinglePieceCoordinates(int row, int col);
    int getRow();
    int getCol();
    void setRow(int row);
    void setCol(int col);
};

class Coordinates {
private:
    int _srcRow;
    int _srcCol;
    int _tgtRow;
    int _tgtCol;

public:
    explicit Coordinates();
    explicit Coordinates(int srcRow, int srcCol, int tgtRow, int tgtCol);

    int getSrcRow() const;
    int getSrcCol() const;
    int getTgtRow() const;
    int getTgtCol() const;
};


#endif //CHESS_COORDINATES_H

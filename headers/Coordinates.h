//
// Created by Ismael Cuevas on 7/14/24.
//

#ifndef CHESS_COORDINATES_H
#define CHESS_COORDINATES_H


class Coordinates {
private:
    int _srcX;
    int _srcY;
    int _tgtX;
    int _tgtY

    explicit Coordinates(): _srcX(0), _srcY(0), _tgtX(0), _tgtY(0) {}
    explicit Coordinates(int srcX, int srcY, int tgtX, int tgtY): _srcX (srcX), _srcY(srcY), _tgtX(tgtX), _tgtY(tgtY) {}

    int getSrcX() const {
      return _srcX;
    }

    int getSrcY() const {
      return _srcY;
    }

    int getTgtX() const {
      return _tgtX;
    }

    int getTgtY() const {
      return _tgtY;
    }
};


#endif //CHESS_COORDINATES_H

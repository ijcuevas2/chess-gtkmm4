//
// Created by Ismael Cuevas on 8/9/24.
//

#ifndef CHESS_POINT2D_H
#define CHESS_POINT2D_H

#include <cstddef>
#include <vector>
#include <unordered_map>
#include <functional>

class Point2D {
private:
    int row;
    int col;
public:
    Point2D();
    Point2D(int row, int col);
    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);
    bool operator==(const Point2D & other) const;

    class HashFunction {
    public:
        size_t operator()(const Point2D & p) const;
    };
};

namespace std {
  template<>
  class hash<Point2D> : public Point2D::HashFunction {
  public:
      using Point2D::HashFunction::operator();
  };
}

#endif //CHESS_POINT2D_H

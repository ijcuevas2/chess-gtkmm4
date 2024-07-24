//
// Created by Ismael Cuevas on 7/22/24.
//

#include "ChessBoard/ChessBoardController.h"
void ChessBoardController::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
  int cellSize = std::min(width, height) / chessBoardModel.getBoardSize();

  // Draw the board
  for (int row = 0; row < chessBoardModel.getBoardSize(); ++row) {
    for (int col = 0; col < chessBoardModel.getBoardSize(); ++col) {
      if ((row + col) % 2 == 0) {
        cr->set_source_rgb(1.0, 0.9, 0.8);
      }
      else {
        cr->set_source_rgb(0.8, 0.6, 0.4);
      }

      cr->rectangle(col * cellSize, row * cellSize, cellSize, cellSize);
      if (this->chessBoardModel.isSelectedBoardSpacePtr(row, col)) {
        cr->set_line_width(4.0);
        cr->fill_preserve();
        cr->set_source_rgb(1.0, 0.65, 0.0);
        cr->fill();
      } else {
        cr->fill();
      }


      // Draw the piece
      ChessPiece* chessPiece = chessBoardModel.getChessPiecePtr(row, col);
      if (chessPiece != nullptr && chessPiece->getPieceType() != PieceType::EMPTY_PIECE) {
        auto pixbuf = chessBoardModel.getPieceImageContent(chessPiece);
        double scale = static_cast<double>(cellSize) / std::max(pixbuf->get_width(), pixbuf->get_height());

        cr->save();
        cr->translate(col * cellSize, row * cellSize);
        cr->scale(scale, scale);

        Gdk::Cairo::set_source_pixbuf(cr, pixbuf, 0, 0);
        cr->paint();
        cr->restore();
      }
    }
  }
}

void ChessBoardController::on_pressed(int n_press, double x, double y, int width, int height) {
  int row = static_cast<int>(y * chessBoardModel.getBoardSize() / height);
  int col = static_cast<int>(x * chessBoardModel.getBoardSize() / width);

  if (!chessBoardModel.hasSelectedBoardSpacePtr()) {
    chessBoardModel.setSelectedBoardSpacePtr(chessBoardModel.getBoardSpacePtr(row, col));
  } else {
    BoardSpace* selectedBoardSpacePtr = chessBoardModel.getSelectedBoardSpacePtr();
    Coordinates coordinates(selectedBoardSpacePtr->getXIndex(), selectedBoardSpacePtr->getYIndex(), row, col);

    ChessPiece* srcChessPiecePtr = selectedBoardSpacePtr->getChessPiecePtr();
    bool canMoveToTarget = srcChessPiecePtr->canMoveToTarget(coordinates);
    bool isTargetTurnPlayersChessPiece = chessBoardModel.isTurnPlayersChessPiece(srcChessPiecePtr, row, col);
    if (canMoveToTarget && !isTargetTurnPlayersChessPiece) {
      ChessPiece* targetChessPiecePtr = chessBoardModel.getChessPiecePtr(row, col);
      bool isDifferentPiece = targetChessPiecePtr != srcChessPiecePtr;
      if (isDifferentPiece) {
        chessBoardModel.assignChessPieceToBoardSpaceIndex(srcChessPiecePtr, row, col);
        chessBoardModel.clearSelectedBoardSpace();
      }
    }

    chessBoardModel.clearSelectedBoardSpacePtr();
  }
}

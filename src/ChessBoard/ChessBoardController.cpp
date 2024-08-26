//
// Created by Ismael Cuevas on 7/22/24.
//

#include "ChessBoard/ChessBoardController.h"

ChessBoardController::ChessBoardController(ChessWindowMediator & chessWindowMediator): chessWindowMediator(chessWindowMediator)  {
}

void ChessBoardController::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height) {
  int cellSize = std::min(width, height) / chessBoardModel.getBoardSize();

  // Draw the board
  for (int row = 0; row < chessBoardModel.getBoardSize(); ++row) {
    for (int col = 0; col < chessBoardModel.getBoardSize(); ++col) {
      // Set the fill color for the rectangle
      if ((row + col) % 2 == 0) {
        cr->set_source_rgb(1.0, 0.9, 0.8);
      } else {
        cr->set_source_rgb(0.8, 0.6, 0.4);
      }

      // Create the rectangle path
      cr->rectangle(col * cellSize, row * cellSize, cellSize, cellSize);

      BoardSpace *boardSpace = chessBoardModel.getBoardSpacePtr(row, col);

      if (boardSpace == nullptr) {
        return;
      }

      bool showMarker = boardSpace->getShowMarker();
      if (chessBoardModel.isSelectedBoardSpacePtr(row, col) || showMarker) {
        cr->set_line_width(4.0);
        cr->fill_preserve();
        cr->set_source_rgb(1.0, 0.65, 0.0);
        cr->fill_preserve();
      } else {
        cr->fill_preserve();
      }

      // Add black outline
      cr->set_source_rgb(0.0, 0.0, 0.0);  // Set color to black
      cr->set_line_width(1.0);  // Set line width for the outline
      cr->stroke();  // Draw the outline

      // Draw the piece
      ChessPiece *chessPiece = chessBoardModel.getChessPiecePtr(row, col);
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

  bool hasSelectedBoardSpacePtr = chessBoardModel.hasSelectedBoardSpacePtr();
  if (!hasSelectedBoardSpacePtr) {
    BoardSpace *boardSpacePtr = chessBoardModel.getBoardSpacePtr(row, col);
    bool isTurnPlayer = chessBoardModel.isTurnPlayer(boardSpacePtr);
    if (isTurnPlayer) {
      chessBoardModel.setSelectedBoardSpacePtr(boardSpacePtr);
    }
  } else {
    BoardSpace *selectedBoardSpacePtr = chessBoardModel.getSelectedBoardSpacePtr();
    bool isSelectedBoardSpacePtr = chessBoardModel.isSelectedBoardSpacePtr(row, col);
    if (!isSelectedBoardSpacePtr) {
      ChessPiece *srcChessPiecePtr = selectedBoardSpacePtr->getChessPiecePtr();
      Point2DPair point2DPair(selectedBoardSpacePtr->getRow(), selectedBoardSpacePtr->getCol(), row, col);
      bool canMoveToTarget = srcChessPiecePtr->canMoveToTarget(point2DPair);
      if (canMoveToTarget) {
        ChessPiece *targetChessPiecePtr = chessBoardModel.getChessPiecePtr(row, col);
        bool isDifferentPiece = targetChessPiecePtr != srcChessPiecePtr;
        if (isDifferentPiece) {
          updateHalfTurnClock(srcChessPiecePtr, targetChessPiecePtr);
          chessBoardModel.clearEnPassantSquare();
          srcChessPiecePtr->afterPieceMoved(point2DPair);
          chessBoardModel.assignChessPieceToBoardSpaceIndex(srcChessPiecePtr, row, col);
          chessBoardModel.clearSelectedBoardSpace();
          chessBoardModel.updateTurnPlayerId();
          chessBoardModel.calculateKingIsInCheck(chessBoardModel.getTurnPlayerId());
          fenModel.saveBoardState();
        }
      }
    }

    resetChessBoardUI();
  }
}

void ChessBoardController::resetChessBoardUI() {
  chessBoardModel.hideHintMarkers();
  chessBoardModel.clearSelectedBoardSpacePtr();
}

void ChessBoardController::updateHalfTurnClock(ChessPiece* srcChessPiecePtr, ChessPiece* targetChessPiecePtr) {
  PieceType targetPieceType = targetChessPiecePtr->getPieceType();
  PieceType srcPieceType = srcChessPiecePtr->getPieceType();
  if (targetPieceType != PieceType::EMPTY_PIECE || srcPieceType == PieceType::PAWN) {
    chessBoardModel.resetHalfMoveClock();
  } else {
    chessBoardModel.incrementHalfMoveClock();
  }
}

void ChessBoardController::loadStateFromFile(std::string filePath) {
  fenModel.loadStateFromFile(filePath);
}

void ChessBoardController::saveStateToFile() {
  fenModel.saveStateToFile();
}

void ChessBoardController::initBoard() {
  chessBoardModel.initBoard();
}

void ChessBoardController::clearBoard() {
  chessBoardModel.clearBoard();
}

PlayerID ChessBoardController::getTurnPlayerId() {
  return chessBoardModel.getTurnPlayerId();
}
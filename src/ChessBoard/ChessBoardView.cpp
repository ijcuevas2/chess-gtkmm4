//
// Created by Ismael Cuevas on 7/16/24.
//

#include "../../headers/ChessBoard/ChessBoardView.h"

ChessBoardView::ChessBoardView() {
  set_content_width(400);
  set_content_height(400);
  set_draw_func(sigc::mem_fun(*this, &ChessBoardView::on_draw));
  add_controller(Gtk::GestureClick::create());
  auto controller = Gtk::GestureClick::create();
  controller->signal_pressed().connect(sigc::mem_fun(*this, &ChessBoardView::on_pressed));
  add_controller(controller);
}

void ChessBoardView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
  int cellSize = std::min(width, height) / chessBoardModel.getBoardSize();

  // Draw the board
  for (int row = 0; row < chessBoardModel.getBoardSize(); ++row) {
    for (int col = 0; col < chessBoardModel.getBoardSize(); ++col) {
      if ((row + col) % 2 == 0)
        cr->set_source_rgb(1.0, 0.9, 0.8); // Light square
      else
        cr->set_source_rgb(0.8, 0.6, 0.4); // Dark square

      cr->rectangle(col * cellSize, row * cellSize, cellSize, cellSize);
      cr->fill();

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

void ChessBoardView::on_pressed(int n_press, double x, double y) {
  int row = static_cast<int>(y * chessBoardModel.getBoardSize() / get_height());
  int col = static_cast<int>(x * chessBoardModel.getBoardSize() / get_width());

  if (!chessBoardModel.hasSelectedBoardSpacePtr()) {
    chessBoardModel.setSelectedBoardSpacePtr(chessBoardModel.getBoardSpacePtr(row, col));
  } else {
    BoardSpace* selectedBoardSpacePtr = chessBoardModel.getSelectedBoardSpacePtr();
    ChessPiece* srcChessPiecePtr = selectedBoardSpacePtr->getChessPiecePtr();
    ChessPiece* targetChessPiecePtr = chessBoardModel.getChessPiecePtr(row, col);
    if (targetChessPiecePtr != srcChessPiecePtr) {
      chessBoardModel.copyChessPieceToIndex(srcChessPiecePtr, row, col);
      srcChessPiecePtr->clearChessPiece();
    }

    chessBoardModel.clearSelectedBoardSpacePtr();
    queue_draw();
  }
}


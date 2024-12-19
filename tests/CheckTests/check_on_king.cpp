//
// Created by Ismael Cuevas on 12/18/24.
//
#include "../test_chess.h"
#include "ChessPiece.h"

class CheckTest : public ::testing::Test {
public:
    ChessMediator chessMediator;
    PlayerID playerId = PlayerID::PLAYER_BLACK;
    ChessBoardModel chessBoardModel{chessMediator};
protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

TEST_F(CheckTest, BasicTest) {
  int row = 0;
  int col = 0;
  ChessPiece* chessPiece = chessBoardModel.getChessPiecePtr(row, col);
  ApprovalTests::Approvals::verify(chessPiece->getPieceType());
}
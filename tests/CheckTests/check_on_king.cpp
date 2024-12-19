//
// Created by Ismael Cuevas on 12/18/24.
//
#include "../test_chess.h"

class CheckTest : public ::testing::Test {
public:
    ChessMediator chessMediator;
    PlayerID playerId = PlayerID::PLAYER_BLACK;
    ChessBoardModel chessBoardModel{chessMediator};
protected:
  void SetUp() override {
    chessBoardModel.initBoard();
  }

  void TearDown() override {
  }
};

TEST_F(CheckTest, BasicTest) {
  int row = 0;
  int col = 0;
  ChessPiece* chessPiece = chessBoardModel.getChessPiecePtr(row, col);
  PieceType pieceType  = chessPiece->getPieceType();
  std::string pieceTypeString = StringUtils::getPieceTypeName(pieceType);
  ApprovalTests::Approvals::verify(pieceTypeString);
}
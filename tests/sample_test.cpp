#include "test_chess.h"
#include "ChessPiece.h"

TEST(SampleTest, ExampleTest) {
  ChessMediator chessMediator;
  PlayerID playerId = PlayerID::PLAYER_BLACK;
  King king(playerId, chessMediator);
  king.setCanCastle(false);
  bool canKingCastle = king.getCanCastle();
  EXPECT_EQ(canKingCastle, false);
}






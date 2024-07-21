//
// Created by Ismael Cuevas on 7/20/24.
//

#ifndef CHESS_CHESSIMAGESINFO_H
#define CHESS_CHESSIMAGESINFO_H

#include <iostream>
#include <map>
#include "../../enum/PieceType.h"
#include "../../enum/Player.h"
#include "gtkmm.h"
#include "../ChessPieces/ChessPiece.h"

class ChessImagesInfo {
public:
    ChessImagesInfo();
    void setChessPieceMap(std::map<PieceType, std::map<PlayerID, std::string>> chessPieceMap);
    void setPiecesContentMap(std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> piecesContentMap);
    Glib::RefPtr<Gdk::Pixbuf> getPieceImageContent(ChessPiece* chessPiece);
private:
    std::string getPieceImagePath(ChessPiece* chessPiece);
    std::map<PieceType, std::map<PlayerID, std::string>> chessPieceMap;
    std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> piecesContentMap;
};


#endif //CHESS_CHESSIMAGESINFO_H

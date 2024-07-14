#include <gtkmm.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include "chess_resources.c"

class ChessBoard : public Gtk::DrawingArea {
public:
    ChessBoard(const std::string& pieces_path = "images/") : pieces_path_(pieces_path) {
        set_content_width(400);
        set_content_height(400);
        set_draw_func(sigc::mem_fun(*this, &ChessBoard::on_draw));
        add_controller(Gtk::GestureClick::create());
        auto controller = Gtk::GestureClick::create();
        controller->signal_pressed().connect(sigc::mem_fun(*this, &ChessBoard::on_pressed));
        add_controller(controller);
        load_pieces();
    }

private:
    const int BOARD_SIZE = 8;
    std::vector<std::vector<std::string>> board = {
        {"DR", "DN", "DB", "DQ", "DK", "DB", "DN", "DR"},
        {"DP", "DP", "DP", "DP", "DP", "DP", "DP", "DP"},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"  ", "  ", "  ", "  ", "  ", "  ", "  ", "  "},
        {"LP", "LP", "LP", "LP", "LP", "LP", "LP", "LP"},
        {"LR", "LN", "LB", "LQ", "LK", "LB", "LN", "LR"}
    };

    std::string pieces_path_;
    std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> pieces;
    bool is_piece_selected = false;
    int selected_row = -1;
    int selected_col = -1;

    void load_pieces() {
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        // std::cout << "Looking for pieces in: " << std::filesystem::absolute(pieces_path_) << std::endl;

        std::vector<std::pair<std::string, std::string>> piece_files = {
            {"LK", "light_king.svg"},   
            {"LQ", "light_queen.svg"},  
            {"LR", "light_rook.svg"},
            {"LB", "light_bishop.svg"}, 
            {"LN", "light_knight.svg"}, 
            {"LP", "light_pawn.svg"},
            {"DK", "dark_king.svg"},   
            {"DQ", "dark_queen.svg"},  
            {"DR", "dark_rook.svg"},
            {"DB", "dark_bishop.svg"}, 
            {"DN", "dark_knight.svg"}, 
            {"DP", "dark_pawn.svg"}
        };

     for (const auto& [piece, file] : piece_files) {
            try {
                auto resource_path = "chess_resources/images/" + file;
                pieces[piece] = Gdk::Pixbuf::create_from_resource(resource_path);
            } catch (const Glib::Error& ex) {
                std::cerr << "Error loading piece image: " << ex.what() << std::endl;
            }
        }
    }

    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
        int cellSize = std::min(width, height) / BOARD_SIZE;

        // Draw the board
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                if ((row + col) % 2 == 0)
                    cr->set_source_rgb(1.0, 0.9, 0.8); // Light square
                else
                    cr->set_source_rgb(0.8, 0.6, 0.4); // Dark square

                cr->rectangle(col * cellSize, row * cellSize, cellSize, cellSize);
                cr->fill();

                // Draw the piece
                std::string piece = board[row][col];
                if (piece != "  " && pieces.count(piece) > 0) {
                    auto pixbuf = pieces[piece];
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

    void clearSelectedChessPiecePosition() {
        is_piece_selected = false;
        selected_row = -1;
        selected_col = -1;
    }

    void on_pressed(int n_press, double x, double y) {
        int row = static_cast<int>(y * BOARD_SIZE / get_height());
        int col = static_cast<int>(x * BOARD_SIZE / get_width());

        if (!is_piece_selected) {
            // First click: Select a piece
            if (board[row][col] != "  ") {
                selected_row = row;
                selected_col = col;
                is_piece_selected = true;
                std::cout << "Piece selected at (" << row << ", " << col << ")" << std::endl;
            }
        } else {
            // Second click: Move the piece
            std::string piece = board[selected_row][selected_col];
            board[selected_row][selected_col] = "  ";
            board[row][col] = piece;
            
            std::cout << "Piece moved from (" << selected_row << ", " << selected_col 
                      << ") to (" << row << ", " << col << ")" << std::endl;

            is_piece_selected = false;
            selected_row = -1;
            selected_col = -1;
            queue_draw();
        }
    }
};

class ChessWindow : public Gtk::Window {
public:
    ChessWindow() {
        set_title("Chess GTKMM4");
        set_default_size(400, 400);

        // You can specify the path to the pieces directory here
        m_chessBoard = Gtk::make_managed<ChessBoard>("../images/");
        set_child(*m_chessBoard);
    }

private:
    ChessBoard* m_chessBoard;
};

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("org.gtkmm.example");
    return app->make_window_and_run<ChessWindow>(argc, argv);
}
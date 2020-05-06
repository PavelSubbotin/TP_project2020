#include<iostream>

class MovePhase{
  private:
    int choose_moves(BattleBoard &board_) {
        int acts = DEFAULT.acts;
        while (acts > 0) {
            board_.print();
            std::cout << "You can do " << acts << " actions" << std::endl;
            std::cout << "If you want to move some character enter it's coordinates, else enter 0 0" << std::endl;
            std::pair<int, int> old_coords = INPUT.coords(board_, "move");
            if (old_coords.first == 0 && old_coords.second == 0) {
                break;
            }
            std::cout << "Now, enter new coordinates\n";
            std::pair<int, int> new_coords = INPUT.coords(board_);
            int x = old_coords.first;
            int y = old_coords.second;
            int x_ = new_coords.first;
            int y_ = new_coords.second;
            if (!board_[x][y]->can_go(x, y, x_, y_)) {
                std::cout << "Try again!" << std::endl;
                continue;
            }
            std::cout << x << ' ' << y << ' ' << x_ << ' ' << y_ << ' ' << (board_[x_][y_] == nullptr) << std::endl;
            board_.make_unit(x_, y_, board_[x][y]->get_health(), board_[x][y]->get_attack(), 0, board_[x][y]->get_type());
            std::cout << "-----------" << std::endl;
            board_.delete_unit(x, y);
            acts -= 1;
        }
        return acts;
    }
  public:
    std::pair<int, int> make_moves(BattleBoard &board){
        BattleBoard other_board = board.copy_();
        other_board.change_player();
        int acts1 = choose_moves(board);
        for (int i = 0; i < 20; ++i) {
            std::cout << std::endl;
        }
        int acts2 = choose_moves(other_board);
        board.merge_(other_board, 1);
        board.print();
        return {acts1, acts2};
    }

};

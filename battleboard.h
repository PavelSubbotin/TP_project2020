#include "units.h"
#include <vector>
#include <iostream>
#include<algorithm>

class BattleBoard{
  private:
    int len = DEFAULT.board_len;
    int wid = DEFAULT.board_wid;
    int current_player = 1;
    std::vector<bool> septums;
    std::vector<std::vector<Unit*>> board;
  public:
    BattleBoard(){
        len = DEFAULT.board_len;
        wid = DEFAULT.board_wid;
        current_player = 1;
        /*for (int i = 0; i < len; ++i){
            for (int j = 0; j < wid; ++j){
                board[i][j] = DEFAULT.start_board[i][j];
            }
        }*/
        board.assign(DEFAULT.board_len, std::vector<Unit*> (DEFAULT.board_wid, nullptr));
        septums.assign(DEFAULT.board_wid, false);
        for (int i = 0; i < DEFAULT.septums_quantity; ++i){
            septums[i] = true;
        }
        random_shuffle(septums.begin(), septums.end());
      }
    void print(int type = 0){
        std::cout << "--------------------\n";
        for (int i = 0; i < len / 2; ++i){
            std::cout <<  len - i << ' ';
            for (auto j: board[i]){
                if (j == nullptr){
                    std::cout << 0 << ' ';
                } else if (type == 0) {
                    std::cout << j->get_type()[0] << ' ';
                } else if (type == 1){
                    std::cout << j->get_health() << ' ';
                } else {
                    std::cout << j->get_attack() << ' ';
                }
            }
            std::cout << std::endl;
        }

        std::cout << "  ";
        for (int i = 0; i < wid; ++i){
            if (septums[i]){
                std::cout << "* ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;

        for (int i = len / 2; i < len; ++i){
            std::cout <<  len - i << ' ';
            for (auto j: board[i]){
                if (j == nullptr){
                    std::cout << 0 << ' ';
                } else if (type == 0){
                    std::cout << j->get_type()[0] << ' ';
                } else if (type == 1){
                    std::cout << j->get_health() << ' ';
                } else {
                    std::cout << j->get_attack() << ' ';
                }
            }
            std::cout << std::endl;
        }

        std::cout << "  ";
        for (int i = 1; i < wid + 1; ++i){
            std::cout << i << ' ';
        }
        std::cout << "\n--------------------\n\n";
        std::cout << std::endl;
    }

    int get_len() const {
        return len;
    }
    int get_wid() const {
        return wid;
    }
    bool set_val(int x, int y, Unit* val){
        if (board[x][y] == nullptr){
            board[x][y] = val;
            return 1;
        }
        return 0;
    }
    Unit* get_cell(int x, int y) {
        return board[x][y];
    }
    void update_damage(int x, int y, int add) const {
        board[x][y]->update_damage(add);
    }
    void update_health(int x, int y, int add) const {
        board[x][y]->update_health(add);
    }
    bool get_damage(int x, int y, int damage) const {
        return board[x][y]->get_damage(damage);
    }
    bool engaged(int x, int y) const{
        if (board[x][y] == nullptr) {
            return 0;
        }
        return 1;
    }
    int get_player() const {
        return current_player;
    }
    std::vector<std::vector<Unit*>> get_board() {
        return board;
    }
    std::vector<bool> get_septums() {
        return septums;
    }
   /* class RowProxy {
      private:
        std::vector<Unit*> &vec;
      public:
        RowProxy(int i, std::vector<std::vector<Unit*>> &board_) {
            vec = board_[i];
        }
        RowProxy(){}
        Unit* & operator[](int j) const {
            return vec[j];
        }
    };*/

    std::vector<Unit*> operator[](int i) const {
        return board[i];
    }

    const void merge_(BattleBoard OtherBoard, int type = 0) {
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < wid; ++j) {
                if (type && i < len / 2 && board[i][j] != nullptr) {
                    board[i][j] = nullptr;
                }
                if (type && board[i][j] == nullptr && i >= len / 2) {
                    continue;
                }
                if (board[i][j] == nullptr && OtherBoard[i][j] != nullptr) {
                    if (OtherBoard[i][j]->type == "Archer") {
                       // (*this).set_val(i, j, CREATOR.ArcherCreator_.FactoryMethod());
                        board[i][j] = CREATOR.ArcherCreator_.FactoryMethod(OtherBoard[i][j]->get_health(), OtherBoard[i][j]->get_attack());//OtherBoard[i][j]->get_health(), OtherBoard[i][j]->get_attack());
                    } else if (OtherBoard[i][j]->type == "Warrior") {
                        board[i][j] = CREATOR.WarriorCreator_.FactoryMethod(OtherBoard[i][j]->get_health(), OtherBoard[i][j]->get_attack());
                    } else if (OtherBoard[i][j]->type == "Knight"){
                        board[i][j] = CREATOR.KnightCreator_.FactoryMethod(OtherBoard[i][j]->get_health(), OtherBoard[i][j]->get_attack());
                    }
                }
            }
        }
    }

    BattleBoard copy_() const {
        BattleBoard OtherBoard = BattleBoard();
        for (size_t i = 0; i < septums.size(); ++i) {
            OtherBoard.septums[i] = septums[i];
        }
        OtherBoard.current_player = current_player;
        OtherBoard.wid = wid;
        OtherBoard.len = len;
        OtherBoard.merge_((*this));
        return OtherBoard;
    }
    const void change_player() {
        current_player *= -1;
    }
    int make_unit(int x, int y, int health, int damage, int type, std::string type_ = "") {
        std::cout << health << ' ' << damage << ' ' << type << ' ' << type_ <<  std::endl;
        if (type == 1 || type_ == "Archer") {
            if (health != 0) board[x][y] = CREATOR.ArcherCreator_.FactoryMethod(health, damage);
            else board[x][y] = CREATOR.ArcherCreator_.FactoryMethod();
            return DEFAULT.archer_cost;
        } else if (type == 2 || type_ == "Warrior") {
            if (health != 0) board[x][y] = CREATOR.WarriorCreator_.FactoryMethod(health, damage);
            else board[x][y] = CREATOR.WarriorCreator_.FactoryMethod();
            return DEFAULT.warrior_cost;
        } else if (type == 3 || type_ == "Knight") {
            if (health != 0) board[x][y] = CREATOR.KnightCreator_.FactoryMethod(health, damage);
            else board[x][y] = CREATOR.KnightCreator_.FactoryMethod();
            return DEFAULT.knight_cost;
        }
    }
    void delete_unit(int x, int y) {
        board[x][y] = nullptr;
    }
    void shuffle_septums() {
        random_shuffle(septums.begin(), septums.end());
    }
};


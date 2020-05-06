#include<vector>

class PrepPhase{
  private:
    static void choose_units(BattleBoard &board_) {
        board_.print();
        int money = DEFAULT.money;
        std::cout << "Welcome to the club buddy\n";
        while (money >= DEFAULT.archer_cost || money >= DEFAULT.warrior_cost || money >= DEFAULT.knight_cost){
            std::cout << "You have " << money << " coins\nArcher cost: " <<
            DEFAULT.archer_cost << "\nWarrior cost: " << DEFAULT.warrior_cost << "\nKnight cost: " << DEFAULT.knight_cost << std::endl;
            std::cout << "If you want to buy an archer enter 1, to buy warrior 2 and 3 to buy a knight\n";
            int type = INPUT.input123(money);
            int x_;
            int y_;
            std::pair<int, int> coords = INPUT.coords(board_);
            x_ = coords.first;
            y_ = coords.second;
            std::cout << x_ << ' ' << y_ << std::endl;
            //Unit* chlen = CREATOR.ArcherCreator_.FactoryMethod();
           // exit(0);
            money -= board_.make_unit(x_, y_, 0, 0, type);
            board_.print();
        }
        std::cout << "You run out of money\n";
    }
  public:
    void build(BattleBoard &board_) {
        choose_units(board_);
        for (int i = 0; i < 20; ++i) {
            std::cout << std::endl;
        }
        BattleBoard second_board;
        second_board.change_player();
        choose_units(second_board);
        board_.merge_(second_board);
        board_.print();
    }
};

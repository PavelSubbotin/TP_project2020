#include "battleboard.h"
#include<vector>

class PrepPhase{
    void choose_units(BattleBoard &board_, int cur_player){
        int money = DEFAULTS.money;
        std::cout << "Welcome to the club buddy\n"
        while (money > 0){
            std::cout << "You have " << money << " coins\nArcher cost: " <<
            DEFAULT.archer_cost << "\nWarrior cost: " << DEFAULT.warrior_cost << "\nKnight cost: " << DEFAULT.knight_cost << std::endl;
            std::cout << "If you want to buy an archer enter 1, to buy warrior 2 and 3 to buy a knight\n";
            std::string type = "";
            while (!(type == "1" || type == "2" || type == "3")){
                std::cout << "Try again\n";
                std::cin >> type;
            }
            string x, y;
            std::cout << "Ok, now enter the coordinates\n";
            cin >> x >> y;
            while(x.size() > 1 || y.size() > 1 || x[0] - '0' > board_.wid || y[0] - '0' > board_.len || x <= "0" || y <= "0"){
                std::cout << "Try again\n";
                std::cin >> x >> y;
            }
            int x_ = x[0] - '1';
            int y_ = y[0] - '1';
            x_ = board_.len - x_ - 1;
            if (type == "1") board_.board[x_][y_] = Creator_.ArcherCreator_.FactoryMethod();
            else if (type == "2") board_.board[x_][y_] = Creator_.WarriorCreator_.FactoryMethod();
            else if (type == "3") board_.board[x_][y_] = Creator_.KnightCreator_.FactoryMethod();
            money -= 3;
        }
    }
};

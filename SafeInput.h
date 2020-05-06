#include<iostream>

class SecureInput{
  public:
    const std::pair<int, int> coords(BattleBoard &board_, std::string type = "build") const {
        std::cout << "player: " << board_.get_player() << std::endl;
        std::string x, y;
        std::cout << "Ok, now enter the coordinates\n";
        while (true) {
            std::cin >> x;
            if (x == "end" && (type == "move" || type == "attack")) {
                return {0, 0};
            }
            if (x == "health") {
                board_.print(1);
                return coords(board_, type);
            }
            if (x == "damage") {
                board_.print(2);
                return coords(board_, type);
            }
            if (x == "units") {
                board_.print();
                return coords(board_, type);
            }
            std::cin >> y;
            if (x.size() != 1 || y.size() != 1) {
                std::cout << "Try again\n";
                continue;
            }
            int x_ = x[0] - '0';
            int y_ = y[0] - '0';
            if (x_ < 1 || x_ > board_.get_wid() || y_ < 1 || y_ > board_.get_len()) {
                std::cout << "Try again\n";
                continue;
            }
            if (board_.get_player() == 1 && y_ > board_.get_len() / 2 || board_.get_player() == -1 && y_ <= board_.get_len() / 2) {
                std::cout << "Try again\n";
                continue;
            }
            y_ = board_.get_len() - (y[0] - '0');
            x_ = x[0] - '0' - 1;
            std::swap(x_, y_);
            if (board_.engaged(x_, y_) && type == "build" || !board_.engaged(x_, y_) && type != "build") {
                std::cout << "Try again\n";
                continue;
            }
            break;
        }
        int y_ = board_.get_len() - (y[0] - '0');
        int x_ = x[0] - '0' - 1;
        return {y_, x_};
    }

    int input123(int money) {
        std::string type = "";
        while (true){
            std::cin >> type;
            if (!(type == "1" || type == "2" || type == "3")){
                std::cout << "Try again\n";
                continue;
            }
            if (type == "1" && money < DEFAULT.archer_cost || type == "2" && money < DEFAULT.warrior_cost
                    || type == "3" && money < DEFAULT.knight_cost){
                std::cout << "You don't have enough money, try again\n";
                continue;
            }
            break;
        }
        return type[0] - '0';
    }

};

SecureInput INPUT;

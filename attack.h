#include<vector>
#include<set>

struct attack{
    int x;
    int y;
    int damage;
    attack(){}
    attack(int x_, int y_, int damage_) {
        x = x_;
        y = y_;
        damage = damage_;
    }
};

class AttackPhase{
  private:
    const std::vector<attack> choose_targets(BattleBoard &board_, int acts) {
        std::vector<attack> attacks;
        while (acts > 0) {
            std::set<std::pair<int, int> > used;
            std::cout << "You can make " << acts << " attacks" << std::endl;
            std::pair<int, int> attacker_coords = INPUT.coords(board_, "attack");
            if (attacker_coords.first == 0 && attacker_coords.second == 0) {
                break;
            }
            board_.change_player();
            std::pair<int, int> target_coords = INPUT.coords(board_, "attack");
            board_.change_player();
            int x = attacker_coords.first;
            int y = attacker_coords.second;
            int x_ = target_coords.first;
            int y_ = target_coords.second;
            if (!(board_[x][y]->can_attack(x, y, x_, y_, board_.get_board(), board_.get_septums()))) {
                std::cout << "You can't do that\n" << "Try again" << std::endl;
                continue;
            }

            if (used.count({x, y})) {
                std::cout << "This unit is already attacking!" << std::endl;
            }
            used.insert({x, y});
            attacks.push_back(attack(x_, y_, board_[x][y]->get_attack()));
            acts -= 1;

        }
        return attacks;
    }

    void make_attacks(std::vector<attack> &attacks, BattleBoard &board_) {
        for (attack attack_: attacks) {
            if (!(board_.engaged(attack_.x, attack_.y))) {
                continue;
            }
            if (board_[attack_.x][attack_.y]->get_damage(attack_.damage)) {
                board_.delete_unit(attack_.x, attack_.y);
            }
        }
    }
  public:
    void attack_phase(BattleBoard &board_, int acts1, int acts2) {
        std::vector<attack> attacks1 = choose_targets(board_, acts1);
        board_.change_player();
        std::vector<attack> attacks2 = choose_targets(board_, acts2);
        board_.change_player();
        make_attacks(attacks1, board_);
        make_attacks(attacks2, board_);
        board_.print();
    }

};

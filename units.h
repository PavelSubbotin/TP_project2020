#include "defaults.h"
#include<string>
#include<vector>
#include<iostream>

class Unit {
  public:
    int health {0};
    int damage {0};
    std::string type;
    void update_damage(int add) {
        damage += add;
    }
    void update_health(int add) {
        health += add;
    }
    bool get_damage(int damage) {
        health -= damage;
        return health <= 0 ? 1 : 0;
    }
    int get_health() {
        return health;
    }
    int get_attack() {
        return damage;
    }
    std::string get_type() const {
        return type;
    }
    virtual bool const can_go(int from_x, int from_y, int to_x, int to_y) const {}
    virtual bool const can_attack(int from_x, int from_y, int to_x, int to_y,
                                  std::vector<std::vector<Unit*>> board_, std::vector<bool> septums) const {}

};

class Archer : virtual public Unit {
  public:
    ~Archer(){};
    Archer(int health_ = DEFAULT.archer_health, int damage_ = DEFAULT.archer_damage) {
        std::cout << "huy" << std::endl;
        health = health_;
        damage = damage_;
        type = "Archer";
    }

    bool const can_go(int from_x, int from_y, int to_x, int to_y) const override {
        if (from_x == to_x && abs(from_y - to_y) == 1){
            return true;
        }
        if (from_y == to_y && abs(from_x - to_x) == 1){
            return 1;
        }
        return 0;
    }

    virtual bool const can_attack(int from_x, int from_y, int to_x, int to_y,
                                  std::vector<std::vector<Unit*>> board_, std::vector<bool> septums) const override{
        if (from_y != to_y) {
            return 0;
        }
        if (septums[from_y]) {
            return 0;
        }
        for (int i = std::min(from_x, to_x) + 1; i < std::max(from_x, to_x); ++i){
            if (board_[i][from_y] != nullptr){
                return 0;
            }
        }
        return 1;
    }
};

class Warrior : virtual public Unit {
  public:
    ~Warrior(){};
    Warrior(int health_ = DEFAULT.warrior_health, int damage_ = DEFAULT.warrior_damage) {
        health = health_;
        damage = damage_;
     //
        type = "Warrior";
    }

    bool const can_go(int from_x, int from_y, int to_x, int to_y) const override {
        int x = abs(from_x - to_x);
        int y = abs(from_y - to_y);
        if (x + y == 1 || x == 1 && y == 1){
            return true;
        }
        return false;
    }

    virtual bool const can_attack(int from_x, int from_y, int to_x, int to_y,
                                  std::vector<std::vector<Unit*>> board_, std::vector<bool> septums) const override {
        if (abs(from_x - to_x) != 1){
            return 0;
        }
        if (abs(from_x - to_y) > 1){
            return 0;
        }
        if (septums[to_y]){
            return 0;
        }
        return 1;
    }
};

class Knight : virtual public Unit {
  public:
    ~Knight(){};
    Knight(int health_ = DEFAULT.knight_health, int damage_ = DEFAULT.knight_damage) {
        health = health_;
        damage = damage_;
        type = "Knight";
    }

    bool const can_go(int from_x, int from_y, int to_x, int to_y) const override {
        std::cout << "ya dolbaeb\n";
        int x = abs(from_x - to_x);
        int y = abs(from_y - to_y);
        if (x == 1 && y == 2 || x == 2 && y == 1){
            return true;
        }
        return false;
    }

    virtual bool const can_attack(int from_x, int from_y, int to_x, int to_y,
                                  std::vector<std::vector<Unit*>> board_, std::vector<bool> septums) const override {
        return (*this).can_go(from_x, from_y, to_x, to_y);
    }
};


class Creator {
  public:
    virtual ~Creator(){};
    virtual Unit* FactoryMethod(int health, int damage) const = 0;
};

class ArcherCreator : public Creator {
  public:
    Unit* FactoryMethod(int health = DEFAULT.archer_health, int damage = DEFAULT.archer_damage) const override {
        return new Archer(health, damage);
    }
};

class WarriorCreator : public Creator {
  public:
    Unit* FactoryMethod(int health = DEFAULT.warrior_health, int damage = DEFAULT.warrior_damage) const override {
        return new Warrior(health, damage);
    }
};

class KnightCreator : public Creator {
  public:
    Unit* FactoryMethod(int health = DEFAULT.knight_health, int damage = DEFAULT.knight_damage) const override {
        return new Knight(health, damage);
    }
};

class Creator_{
    public:
        ArcherCreator ArcherCreator_;
        WarriorCreator WarriorCreator_;
        KnightCreator KnightCreator_;
        Creator_(){}
};

const Creator_ CREATOR;

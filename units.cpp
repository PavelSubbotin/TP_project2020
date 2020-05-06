class Defaults_{
  public:
    int archer_health = 0;
    int archer_damage = 0;
    int warrior_health = 0;
    int warrior_damage = 0;
    int knight_health = 0;
    int knight_damage = 0;
};

Defaults_ Default;


//#include "defaults.h"

class Unit {
  public:
    virtual ~Unit() {}
    virtual void update_damage(int add) {}
    virtual void update_health(int add) {}
    virtual int get_damage() {}
    virtual int get_health() {}

};

class Army_unit {
  protected:
    int health;
    int damage;
    void update_damage_(int add) {
        damage += add;
    }
    void update_health_(int add) {
        health += add;
    }
    int get_damage_() {
        return damage;
    }
    int get_health_() {
        return health;
    }
  public:
    Army_unit(){}
    Army_unit(int health_, int damage_){
        int health = health_;
        int damage = damage_;
    }
};

class Archer : public Unit, public Army_unit {
  public:
    ~Archer(){};
    Archer(int health_, int damage_) {
        Army_unit(health_, damage_);
    }
    void update_damage(int add) override {
        (*this).update_damage_(add);
    }
    void update_health(int add) override {
        (*this).update_health_(add);
    }
    int get_damage() override {
        return (*this).get_damage_();
    }
    int get_health() override {
        return (*this).get_health_();
    }
};

class Warrior : public Unit, public Army_unit {
  public:
    ~Warrior(){};
    Warrior(int health_, int damage_) {
        Army_unit(health_, damage_);
    }
    void update_damage(int add) override {
        (*this).update_damage_(add);
    }
    void update_health(int add) override {
        (*this).update_health_(add);
    }
    int get_damage() override {
        return (*this).get_damage_();
    }
    int get_health() override {
        return (*this).get_health_();
    }
};

class Knight : public Unit, public Army_unit {
  public:
    ~Knight(){};
    Knight(int health_, int damage_) {
        Army_unit(health_, damage_);
    }
    void update_damage(int add) override {
        (*this).update_damage_(add);
    }
    void update_health(int add) override {
        (*this).update_health_(add);
    }
    int get_damage() override {
        return (*this).get_damage_();
    }
    int get_health() override {
        return (*this).get_health_();
    }
};


class Creator {
  public:
    virtual ~Creator(){};
    virtual Unit* FactoryMethod() const = 0;
};

class ArcherCreator : public Creator {
  public:
    Unit* FactoryMethod() const override {
        return new Archer(Default.archer_health, Default.archer_damage);
    }
};

class WarriorCreator : public Creator {
  public:
    Unit* FactoryMethod() const override {
        return new Warrior(Default.warrior_health, Default.warrior_damage);
    }
};

class KnightCreator : public Creator {
  public:
    Unit* FactoryMethod() const override {
        return new Knight(Default.knight_health, Default.knight_damage);
    }
};

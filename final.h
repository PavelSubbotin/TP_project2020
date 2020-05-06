class FinalPhase{
  private:
    int winner(BattleBoard &board_) const {
        bool not_null1 = false;
        for (int i = 0; i < board_.get_len() / 2; ++i) {
            for (int j = 0; j < board_.get_wid(); ++j) {
                if (board_.engaged(i, j)) not_null1 = true;
            }
        }
        bool not_null2 = false;
        for (int i = board_.get_len() / 2; i < board_.get_len(); ++i) {
            for (int j = 0; j < board_.get_wid(); ++j) {
                if (board_.engaged(i, j)) not_null2 = true;
            }
        }
        if (not_null1 && not_null2) {
            return 0;
        }
        if (!(not_null1 || not_null2)) {
            return 2;
        }
        if (!not_null1) {
            return 1;
        }
        if (!not_null2) {
            return -1;
        }
    }

    void damage_units(BattleBoard &board_) {
        for (int i = 0; i < board_.get_len(); i++) {
            for (int j = 0; j < board_.get_wid(); ++j) {
                if(!(board_.engaged(i, j))) {
                    continue;
                }
                if (board_[i][j]->get_damage(1)) {
                    board_.delete_unit(i, j);
                }

            }
        }
    }
  public:
    int final_phase(BattleBoard &board_) {
        damage_units(board_);
        return winner(board_);
    }

};
